#include <memory>
#include <glog/logging.h>
#include "opentelemetry/trace/provider.h"
#include "opentelemetry/sdk/trace/simple_processor.h"
#include "opentelemetry/sdk/trace/tracer_provider.h"
#include "opentelemetry/exporters/zipkin/zipkin_exporter.h"
#include "absl/strings/str_format.h"

opentelemetry::exporter::zipkin::ZipkinExporterOptions opts;
namespace trace    = opentelemetry::trace;
namespace nostd    = opentelemetry::nostd;
namespace sdktrace = opentelemetry::sdk::trace;
namespace zipkin   = opentelemetry::exporter::zipkin;

void InitTracer()
{
  // Create zipkin exporter instance
  opentelemetry::sdk::resource::ResourceAttributes attributes = {
      {"service.name", "zipkin_demo_service"}};
  auto resource  = opentelemetry::sdk::resource::Resource::Create(attributes);
  auto exporter  = std::unique_ptr<sdktrace::SpanExporter>(new zipkin::ZipkinExporter(opts));
  auto processor = std::unique_ptr<sdktrace::SpanProcessor>(
      new sdktrace::SimpleSpanProcessor(std::move(exporter)));
  auto provider = nostd::shared_ptr<trace::TracerProvider>(
      new sdktrace::TracerProvider(std::move(processor), resource));
  // Set the global trace provider
  trace::Provider::SetTracerProvider(provider);
}

namespace
{
nostd::shared_ptr<trace::Tracer> get_tracer()
{
  auto provider = trace::Provider::GetTracerProvider();
  return provider->GetTracer("foo_library", OPENTELEMETRY_SDK_VERSION);
}

void f1()
{
  auto scoped_span = trace::Scope(get_tracer()->StartSpan("f1"));
  get_tracer()->GetCurrentSpan()->SetAttribute("att0", 111);
}

void f2()
{
  auto scoped_span = trace::Scope(get_tracer()->StartSpan("f2"));

  f1();
  f1();
}
}  // namespace

void foo_library()
{
  auto scoped_span = trace::Scope(get_tracer()->StartSpan("library"));

  f2();
}

int main(int argc, char** argv) {
    FLAGS_logtostderr = true;
    google::InitGoogleLogging(argv[0]);
    if (argc == 2)
    {
      opts.endpoint = argv[1];
    }
    InitTracer();
    {
        auto scoped_span = trace::Scope(
                get_tracer()->StartSpan("library-loop"));
        for (int i = 0; i < 10; i++) {
            foo_library();
            usleep(1000000);
            get_tracer()->ForceFlushWithMicroseconds(1000);
            LOG(INFO) << absl::StrFormat("foo library call");
        }
    }
    return 0;
}
