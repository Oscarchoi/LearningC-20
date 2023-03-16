#include <experimental/coroutine>
#include <iostream>
#include <memory>

template <typename T>
struct MyFuture {
  std::shared_ptr<T> value;

  MyFuture(std::shared_ptr<T> p) : value(p) {
    std::cout << "  MyFuture::MyFuture()\n";
  }
  ~MyFuture() { std::cout << "  MyFuture::~MyFuture()\n"; }

  T get() {
    std::cout << "  MyFuture::get()\n";
    return *value;
  }

  struct promise_type {
    std::shared_ptr<T> ptr = std::make_shared<T>();
    promise_type() {
      std::cout << "	promise_type::promise_type()" << std::endl;
    }
    ~promise_type() {
      std::cout << "	promise_type::~promise_type()" << std::endl;
    }
    MyFuture<T> get_return_object() {
      std::cout << "	promise_type::get_return_object()\n";
      return ptr;
    }
    void return_value(T v) {
      std::cout << "	promise_type::return_value(...)\n";
      *ptr = v;
    }
    std::experimental::suspend_never initial_suspend() {
      std::cout << "	promise_type::initial_suspend()\n";
      return {};
    }
    std::experimental::suspend_never final_suspend() noexcept {
      std::cout << "	promise_type::final_suspend()\n";
      return {};
    }
    void unhandled_exception() { std::exit(1); }
  };
};

MyFuture<int> createFuture() {
  std::cout << "createFuture\n";
  co_return 2021;
}

int main() {
  auto future = createFuture();
  auto res = future.get();
  std::cout << "res: " << res << std::endl;
}
