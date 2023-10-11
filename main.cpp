#include <iostream>
#include <thread>
#include <mutex>
#include <ctime>
#include <vector>

using namespace std;

vector <string> all_order;
vector <string> ready_dish;
mutex mtx;
mutex mtx2;
string dish;

// прием заказов
void orders()
{
  string food[5] = {"pizza", "soup", "steak", "salad", "sushi"};
  string name_food;   
  while(1)
  {
    int time1 = rand() % 6 + 5;
    this_thread :: sleep_for(chrono :: seconds(time1));
    int num = rand() % sizeof(food) / sizeof(food[0]);
    name_food = food[num];
    cout << "the waiter took a new order for: " << name_food  << endl;
    mtx.lock();
    all_order.push_back(name_food);
    mtx.unlock();

  }
}

// приготовление заказа
void chickens()
{
  while(1)
  {
    
    int time2 = rand() % 11 + 5;
    this_thread :: sleep_for(chrono :: seconds(time2));
    dish = all_order[0];
    mtx.lock();
    all_order.erase(all_order.begin());
    mtx.unlock(); 
    mtx2.lock();
    ready_dish.push_back(dish);
    cout << "dish " << dish << " ready" << endl;
    mtx2.unlock();
  }
    
}



    

int main()
{
    srand(time(0));
    int count = 1;
    
    thread order(orders);
    order.detach();

    thread chicken(chickens);
    chicken.detach();

    // доставка заказа 
    while(count <= 10)
    {
      this_thread :: sleep_for(chrono :: seconds(30));
      cout << "the courier picked up the order " << count ++ << endl;
      mtx2.lock();
      for(int i = 0; i < ready_dish.size(); i ++)
      {
          cout << ready_dish[i] << endl;
      }

      ready_dish.clear();
      mtx2.unlock();
    }
  

 return 0;
  
    
}