#include <cmath>
#include <iostream>
#include <exception>
#include "token.hpp"

double expression();
double term();
double primary();
double number();

Token_stream ts;

double expression() {
  double lval = term(), rval;
  Token tok;
  while (true) {
    tok = ts.peek();
    switch (tok.type) {
      case ADD:
        ts.pop();
        lval += term();
        break;
      case SUB:
        ts.pop();
        lval -= term();
        break;
      default:
        return lval;
    }
  }
};

double term() {
  double lval = primary(), rval;
  Token tok;
  while (true) {
    tok = ts.peek();
    switch (tok.type) {
      case MUT:
        ts.pop();
        lval *= primary();
        break;
      case DIV:
        ts.pop();
        rval = primary();
        if (rval == 0)
          throw std::runtime_error("除数不能为 0");
        lval /= rval;
        break;
      default:
        return lval;
    }
  }
}

double primary() {
  auto tok = ts.peek();
  if (tok.type == L_PAR) {
    ts.pop();
    auto val = expression();
    if (ts.peek().type != R_PAR) {
      throw std::runtime_error("括号未闭合");
    } else {
      ts.pop();
    }
    return val;
  } else if (tok.type == SUB) {
    ts.pop();
    return -primary();
  } else {
    double val = number();
    while (true) {
      tok = ts.peek();
      switch (tok.type) {
        case POW:
          ts.pop();
          val = std::pow(val, primary());
          break;
        case EXP:
          ts.pop();
          val = val * std::pow(10, primary());
          break;
        default:
          return val;
      }
    }
  }
}

double number() {
  Token tok = ts.peek();
  if (tok.type == NUM) {
    ts.pop();
    return tok.value;
  }
  throw std::runtime_error("运算符缺少数字");
}

int main() {
  double ans;
  std::cout << "带括号的数学四则运算计算器" << std::endl
            << "键入表达式，按下回车键" << std::endl;
  while (true) {
    try {
      std::cout << "> ";
      ans = expression();
      if (ts.peek().type != END) {
        throw std::runtime_error("非法表达式");
      } else {
        std::cout << "= " << ans << std::endl;
      }
    } catch (std::exception& e) {
      std::cout << e.what() << std::endl;
    }
    ts.clear();
  }
}