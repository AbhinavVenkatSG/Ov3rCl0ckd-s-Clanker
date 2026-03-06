#include <stdio.h>
#include <math.h>

typedef struct {
      float weights;
      float bias;
}Node;

//Input -> weighted sum [ f(w*x + b) ]

int main() {
      //simple equation y = 2x
      //but the mode does not know its 2 so we need to somehow make it find 2
      float input[]= {1.0, 2.0, 3.0, 4.0, 5.0};
      float output[] ={2.0,4.0,6.0,8.0,10.0};
      Node node;
  node.weights = 0.0;
  node.bias = 0.0;
  float learning_rate = 0.01;
  
      printf("Test\n");
      return 0;
}
