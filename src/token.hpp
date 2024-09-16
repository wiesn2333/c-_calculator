enum Type { END, ADD, SUB, MUT, DIV, L_PAR, R_PAR, NUM };

class Token {
public:
  Type type;
  double value;
};

class Token_stream {
public:
  Token get();
  Token peek();
  void clear();
  void putback(Token k);

private:
  bool hasbuf = false;
  Token buffer;
};