-include ../makefile.inc

CPU_TARGETS = IVFFlat

default: cpu

cpu: $(CPU_TARGETS)

%: %.cpp ../libfaiss_$(TARGET).a
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) -I ../.. $(LIBS)

clean:
	rm -f $(CPU_TARGETS) $(GPU_TARGETS)

.PHONY: all cpu default clean
