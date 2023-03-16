#include <experimental/coroutine>
#include <iostream>
#include <memory>

template <typename T>
struct MyFuture {
  struct promise_type;
  using handle_type = std::experimental::coroutine_handle<promise_type>;
  handle_type coro;

  MyFuture(handle_type h) : coro(h) {
    std::cout << "  MyFuture::MyFuture()" << std::endl;
  }
  ~MyFuture() {
    std::cout << "  MyFuture::~MyFuture()" << std::endl;
    if (coro) coro.destroy();
  }

  T get() {
    std::cout << "  MyFuture::get()" << std::endl;
    coro.resume();
    return coro.promise().result;
  }

  struct promise_type {
    T result;
    promise_type() {
      std::cout << "	promise_type::promise_type()" << std::endl;
    }
    ~promise_type() {
      std::cout << "	promise_type::~promise_type()" << std::endl;
    }
    MyFuture<T> get_return_object() {
      std::cout << "	promise_type::get_return_object()\n";
      return MyFuture(handle_type::from_promise(*this));
    }
    void return_value(T v) {
      std::cout << "	promise_type::return_value(...)\n";
      result = v;
    }
    std::experimental::suspend_always initial_suspend() {
      std::cout << "	promise_type::initial_suspend()\n";
      return {};
    }
    std::experimental::suspend_always final_suspend() noexcept {
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
  // auto res = future.get();
  // std::cout << "res: " << res << std::endl;
}
