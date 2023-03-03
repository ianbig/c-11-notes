#include <iostream>
#include <memory>

class Investment {
  public:
  Investment() {
    std::cout << "Investment is constructed" << std::endl;
  }

  virtual ~Investment() {
    std::cout << "Investment is destroyed" << std::endl;
  }

  Investment(Investment && rhs) {
    std::cout << "Investment is moved" << std::endl;
  }
};

class Bond : public Investment {
  public:
  Bond() {
    std::cout << "Bond is constructed" << std::endl;
  }

  virtual ~Bond() {
    std::cout << "Bond is destroyed" << std::endl;
  }
};

class Stock: public Investment {
  public:
  Stock() {
    std::cout << "Stock is constructed" << std::endl;
  }

  virtual ~Stock() {
    std::cout << "Stock is destroyed" << std::endl;
  }

  Stock(Stock && rhs) {
    std::cout << "Stock Move constructor is called" << std::endl;
  }
};

enum class Opts {
  STOCK,
  BOND,
};

std::unique_ptr<Investment> makeInvestment(Opts options) {
  if (options == Opts::STOCK) {
    return std::make_unique<Stock>();
  }

  return std::make_unique<Bond>();
}

std::unique_ptr<Investment>&& transferOwnership(std::unique_ptr<Investment> & ptr) {
  return std::move(ptr);
}

int main() {
  auto investment = makeInvestment(Opts::STOCK);
  auto investmentII = transferOwnership(investment);

  std::shared_ptr<Investment> si = makeInvestment(Opts::BOND); // this line is weird since the next line would have compile error
  // std::shared_ptr<Investment> si2 = investmentII;

  // the line 70 and 71 leads to segementation fault
  Investment *p = new Investment();
  std::shared_ptr<Investment> up(p), up2(p);
}