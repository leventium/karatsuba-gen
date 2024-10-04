#ifndef INCLUDE_SRC_RESULT_H_
#define INCLUDE_SRC_RESULT_H_

template <typename T, typename E> class Result {
private:
  T val_;
  E err_;
  bool is_err;

  Result() = default;

public:
  Result(T val) {
    val_ = val;
    is_err = false;
  };
  ~Result() {
    if (is_err)
      err_.~E();
    else
      val_.~T();
  };
  static Result error(E err) {
    Result obj;
    obj.err_ = err;
    obj.is_err = true;
    return obj;
  };
  bool is_error() { return is_err; };
  T &operator*() { return val_; };
  E &err() { return err_; };
};

#endif // INCLUDE_SRC_RESULT_H_
