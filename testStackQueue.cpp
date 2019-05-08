#define CATCH_CONFIG_MAIN
#include <iostream>
#include "cs221util/catch.hpp"
#include "stack.h"
#include "queue.h"
//using namespace cs221util;
using namespace std;
TEST_CASE("deque::basic functions", "[weight=1][part=stack]"){
  Deque<int> intDeque;
  vector<int> result;
  vector<int> expected;
  for(int i = 10; i > 0; i--){
    intDeque.pushR(i);
    expected.push_back(i);
  }
  for(int j = 10; j > 0; j--){
    result.push_back(intDeque.popL());

  }
  REQUIRE(result == expected);
}
//////

TEST_CASE("stack::basic functions","[weight=1][part=stack]"){
    Stack<int> intStack;
    vector<int> result;
    vector<int> expected;
    for (int i = 10; i > 0; i--) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        intStack.push(i);
    }
    while (!intStack.isEmpty()) {
      int temp = intStack.pop();
      cout<<temp<<endl;
        result.push_back(temp);
    }
    REQUIRE( result == expected);
    cout<<"STACK DONE"<<endl;
}
TEST_CASE("queue::basic functions","[weight=1][part=queue]"){
    Queue<int> intQueue;
    vector<int> result;
    vector<int> expected;
    for (int i = 1; i <= 10; i++) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        intQueue.enqueue(i);
    }
    while (!intQueue.isEmpty()) {
        result.push_back(intQueue.dequeue());
    }
    REQUIRE( result == expected);
}
