#include <stdio.h>
#include <math.h>

#define NUM_CLASSES 5
#define NUM_SAMPLES 5

typedef struct {
    float weights[NUM_CLASSES];
    float biases[NUM_CLASSES];
    float probabilities[NUM_CLASSES];
} MultiNode;

float class_values[NUM_CLASSES] = {4.0, 6.0, 8.0, 10.0, 12.0};
float inputs[NUM_SAMPLES] = {2.0, 3.0, 4.0, 5.0, 6.0};
int targets[NUM_SAMPLES] = {0, 1, 2, 3, 4}; 

void softmax(float *input, float *output, int n) {
    float sum = 0;
    for (int i = 0; i < n; i++) {
        output[i] = expf(input[i]);
        sum += output[i];
    }
    for (int i = 0; i < n; i++) output[i] /= sum;
}

void train(MultiNode *n) {
    float lr = 0.1;
    for (int epoch = 0; epoch < 2000; epoch++) {
        for (int s = 0; s < NUM_SAMPLES; s++) {
            float raw_out[NUM_CLASSES];
            for (int i = 0; i < NUM_CLASSES; i++) {
                raw_out[i] = (inputs[s] * n->weights[i]) + n->biases[i];
            }
            
            softmax(raw_out, n->probabilities, NUM_CLASSES);

            for (int i = 0; i < NUM_CLASSES; i++) {
                float target_prob = (i == targets[s]) ? 1.0f : 0.0f;
                float error = n->probabilities[i] - target_prob;
                
                n->weights[i] -= lr * error * inputs[s];
                n->biases[i] -= lr * error;
            }
        }
    }
}

void predict_and_rank(MultiNode *n, float user_input) {
    float raw_out[NUM_CLASSES];
    for (int i = 0; i < NUM_CLASSES; i++) {
        raw_out[i] = (user_input * n->weights[i]) + n->biases[i];
    }
    softmax(raw_out, n->probabilities, NUM_CLASSES);

    int indices[NUM_CLASSES] = {0, 1, 2, 3, 4};
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < NUM_CLASSES; j++) {
            if (n->probabilities[indices[j]] > n->probabilities[indices[i]]) {
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
        printf("%d Choice: %.1f (Confidence: %.2f%%)\n", i + 1, class_values[indices[i]], n->probabilities[indices[i]] * 100);
    }
}

int main() {
    MultiNode model = {0}; 
    printf("Training Neural Network to recognize pattern y=2x...\n");
    train(&model);

    float user_val;
    while (1) {
        printf("\n--- Neural Predictor ---\n");
        printf("Enter an input number (or -1 to quit): ");
        if (scanf_s("%f", &user_val) != 1 || user_val == -1) break;

        printf("\nNeural Network Predictions:\n");
        predict_and_rank(&model, user_val);
    }

    return 0;
}
