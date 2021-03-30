## Kernel Configuration
```
CONFIG_FUNCTION_TRACER
CONFIG_FUNCTION_GRAPH_TRACER
CONFIG_STACK_TRACER
CONFIG_DYNAMIC_FTRACE
```
## Steps
```
cd /sys/kernel/debug/tracing
cat available_tracers
echo function > current_tracer
echo function_graph > current_tracer
echo do_page_fault > set_ftrace_filter
echo hello world > trace_marker
echo 1 > events/sched/sched_switch/enable
```

## Reading
* https://www.kernel.org/doc/Documentation/trace/ftrace.txt
* https://lwn.net/Articles/365835/
* https://lwn.net/Articles/366796/
* https://elinux.org/Ftrace
