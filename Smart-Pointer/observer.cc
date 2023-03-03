#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>
#include <string>

class Subscriber {
  public:
  virtual void update() = 0;
};

class Store {
  using vecWeakPtr = std::vector<std::weak_ptr<Subscriber>>;
  using mapvec = std::unordered_map<std::string, vecWeakPtr>;
  mapvec listeners;
  public:
  Store() = default;
  void addSubscriber(std::string eventType, std::shared_ptr<Subscriber> & listener) {
    listeners[eventType].push_back(listener);
  }

  void deleteSubscriber(std::string eventType, std::shared_ptr<Subscriber> & listener) {
    for (auto it = listeners[eventType].begin(); it != listeners[eventType].end(); it++) {
      auto curFound = it->lock();
      if (curFound != nullptr && curFound == listener) {
        listeners[eventType].erase(it);
        return;
      }
    }
  }

  void notify(std::string eventType) {
    auto matchedTypeListeners = listeners[eventType];
    for (auto it = matchedTypeListeners.begin(); it != matchedTypeListeners.end(); it++) {
      auto sub = it->lock();
      if (sub != nullptr) {
        sub->update();
      }
    }
  }

  void importNewInventory(std::string msg) {
    //ops of buying new stuff
    notify(msg);
  }
};

class IphoneSubscriber : public Subscriber {
  public:
  IphoneSubscriber() = default;
  virtual void update() {
    std::cout << "get new Ipone, go to apple store :)" << std::endl;
  }
};

class MacBookSubsriber : public Subscriber {
  public:
  MacBookSubsriber() = default;
  virtual void update() {
    std::cout << "get new Mac, go to apple store :)" << std::endl;
  }
};

int main() {
  Store st;
  std::shared_ptr<Subscriber> computerLover = std::make_shared<MacBookSubsriber>();
  std::shared_ptr<Subscriber> phoneLover = std::make_shared<IphoneSubscriber>();
  st.addSubscriber("newPhone", phoneLover);
  st.addSubscriber("newPC", computerLover);

  st.importNewInventory("newPhone");
  st.importNewInventory("newPC");
  st.importNewInventory("new");

  st.deleteSubscriber("newPC", computerLover);
  st.importNewInventory("newPC");
}