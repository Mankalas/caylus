#include <boost/thread.hpp>
#include <boost/signal.hpp>
#include <boost/bind.hpp>
#include <iostream>

class View;

class Controller
{
public:
  Controller(){};

  boost::mutex mut;
  boost::condition_variable view_connected;
  boost::condition_variable ready;

  View* v;

  void addView(View* view)
  {
    std::cout << "Here comes a new challenger.\n";
    this->v = view;
    view_connected.notify_one();
  }

  boost::signal<unsigned (unsigned)>* getSignal()
  {
    return &signal;
  }

  void operator()();

private:
  boost::signal<unsigned (unsigned)> signal;
};

class View
{
public:
  boost::signal<void (void)> signal;
  boost::mutex mut;
  boost::condition_variable view_connected;

  View(Controller* c)
    :c_(c)
  {
    c_->getSignal()->connect(boost::bind(&View::ask, this, _1));
    c_->addView(this);
    c->mut.unlock();
  };

  void operator()()
  {
    boost::unique_lock<boost::mutex> lock(mut);
    view_connected.wait(lock);
    std::cout << "Disconnected.\n";
  };

  unsigned ask(unsigned i)
  {
    unsigned response;
    while ((std::cout << "Response?") && !(std::cin >> response))
    {
      std::cout << "Bad number.\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return response + 1;
  }

private:
  Controller* c_;
};

void Controller::operator()()
{
    std::cout << "Waiting for challenger.\n";
    ready.notify_one();
    boost::unique_lock<boost::mutex> lock(mut);
    view_connected.wait(lock);
    unsigned response = signal(1);
    std::cout << "Response : " << response << "\nDisconnecting views...";
    v->view_connected.notify_one();
};

int main()
{
  Controller c;

  boost::thread controller_thread = boost::thread(boost::ref(c));

  boost::unique_lock<boost::mutex> lock(c.mut);
  c.ready.wait(lock);
  std::cout << "Controller ready\n";

  View v(&c);
  boost::thread view_thread = boost::thread(boost::ref(v));
  controller_thread.join();

}
