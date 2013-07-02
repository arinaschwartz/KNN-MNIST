ifeq ($(DEBUG),yes)
  OPTIMIZE_FLAG = -O0 -g -DDEBUG
else
  OPTIMIZE_FLAG = -O3
endif


OBJS = MNISTDataset.o MNISTImage.o MNISTImageImpls.o knn.o
DEPS = $(OBJS:.o=.d)
CXX = g++
CXXFLAGS = -Wall -MMD -MP $(OPTIMIZE_FLAG)
BIN = mnist-knn mnist-knn-tests

all: mnist-knn

tests: mnist-knn-tests

mnist-knn: $(OBJS) mnist-knn.o
	$(CXX) $(LDFLAGS) $(LDLIBS) $(OBJS) mnist-knn.o -o $@

mnist-knn-tests: $(OBJS) mnist-knn-tests.o
	$(CXX) $(LDFLAGS) $(LDLIBS) $(OBJS) mnist-knn-tests.o -o $@
		
%.d: %.cpp

clean:
	-rm -f $(OBJS) $(BIN) *.d
	
-include $(DEPS)
