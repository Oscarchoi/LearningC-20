#include <experimental/coroutine>
#include <iostream>

struct MySuspendAlways {
  bool await_ready() const noexcept {
    std::cout << "    MySuspendAlways::await_ready" << std::endl;
    return false;
  }

  void await_suspend(std::experimental::coroutine_handle<>) const noexcept {
    std::cout << "    MySuspendAlways::await_suspend" << std::endl;
  }

  void await_resume() const noexcept {
    std::cout << "    MySuspendAlways::await_resume" << std::endl;
  }
};

struct MySuspendNever {
  bool await_ready() const noexcept {
    std::cout << "    MySuspendNever::await_ready" << std::endl;
    return true;
  }

  void await_suspend(std::experimental::coroutine_handle<>) const noexcept {
    std::cout << "    MySuspendNever::await_suspend" << std::endl;
  }

  void await_resume() const noexcept {
    std::cout << "    MySuspendNever::await_resume" << std::endl;
  }
};

struct Job {
  struct promise_type;
  using handle_type = std::experimental::coroutine_handle<promise_type>;
  handle_type coro;

  Job(handle_type h) : coro(h) {}
  ~Job() {
    if (coro) coro.destroy();
  }

  void start() { coro.resume(); }

  struct promise_type {
    promise_type() {}
    ~promise_type() {}

    MySuspendAlways initial_suspend() {
      std::cout << "  Job prepared" << std::endl;
      return {};
    }
    MySuspendAlways final_suspend() noexcept {
      std::cout << "  Job finished" << std::endl;
      return {};
    }
    auto get_return_object() { return Job(handle_type::from_promise(*this)); }
    void return_void() {}
    void unhandled_exception() {}
  };
};