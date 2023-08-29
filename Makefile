
CFLAGS = -std=c++17 -I. -I/Users/tomnom/VulkanSDK/1.3.250.1/macOS/include -I/opt/homebrew/include
LDFLAGS = -L/Users/tomnom/VulkanSDK/1.3.250.1/macOS/lib -L/opt/homebrew/lib `pkg-config --static --libs glfw3` -lvulkan

a.out: *.cpp *.hpp
	g++ $(CFLAGS) -o a.out *.cpp $(LDFLAGS)

.PHONY: test clean

test: a.out
	./a.out

clean:
	rm -f a.out
