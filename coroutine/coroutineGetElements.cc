#include <experimental/coroutine>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

template <typename T>
struct Generator {
  struct promise_type;
  using handle_type = std::experimental::coroutine_handle<promise_type>;
  handle_type coro;

  Generator(handle_type h) : coro(h) {}

  ~Generator() {
    if (coro) coro.destroy();
  }

  Generator(const Generator&) = delete;
  Generator& operator=(const Generator&) = delete;
  Generator(Generator&& oth) : coro(oth.coro) { oth.coro = nullptr; }
  Generator& operator=(Generator& oth) {
    coro = oth.coro;
    oth.coro = nullptr;
    return *this;
  }
  T getNextValue() {
    coro.resume();
    return coro.promise().current_value;
  }

  struct promise_type {
    promise_type(){}
    ~promise_type() {}

    std::experimental::suspend_always initial_suspend() { return {}; }
    std::experimental::suspend_always final_suspend() noexcept { return {}; }
    auto get_return_object() {
      return Generator(handle_type::from_promise(*this));
    }
    std::experimental::suspend_always yield_value(const T value) {
      current_value = value;
      return {};
    }
    void return_void() {}
    void unhandled_exception() { std::exit(1); }
    T current_value;
  };
};

template <typename Cont>
Generator<typename Cont::value_type> getNext(Cont cont) {
  for (auto c : cont) co_yield c;
}

int main() {
  std::string helloworld = "Hello world";
  auto gen = getNext(helloworld);
  for (int i = 0; i < helloworld.size(); ++i) {
    std::cout << gen.getNextValue() << " ";
  }
  std::cout << "\n" << std::endl;

  std::vector myVector{1, 2, 3, 4, 5};
  auto gen2 = getNext(myVector);
  for (int i = 0; i < myVector.size(); ++i) {
    std::cout << gen2.getNextValue() << " ";
  }
  std::cout << "\n" << std::endl;

  return 0;
}