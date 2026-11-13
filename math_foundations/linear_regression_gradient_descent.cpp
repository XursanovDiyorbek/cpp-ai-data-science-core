#include <iostream>
#include <vector>

void trainLinearRegression(const std::vector<double>& x, const std::vector<double>& y, double& weight, double& bias, double learningRate, int epochs) {
    int n = x.size();
    for (int epoch = 0; epoch < epochs; ++epoch) {
        double weightGradient = 0.0;
        double biasGradient = 0.0;
        for (int i = 0; i < n; ++i) {
            double prediction = weight * x[i] + bias;
            double error = prediction - y[i];
            weightGradient += (2.0 / n) * error * x[i];
            biasGradient += (2.0 / n) * error;
        }
        weight -= learningRate * weightGradient;
        bias -= learningRate * biasGradient;
    }
}

int main() {
    std::vector<double> x = {1.0, 2.0, 3.0, 4.0, 5.0};
    std::vector<double> y = {2.0, 4.0, 6.0, 8.0, 10.0};

    double weight = 0.0;
    double bias = 0.0;
    double learningRate = 0.01;
    int epochs = 1000;

    trainLinearRegression(x, y, weight, bias, learningRate, epochs);

    std::cout << "Trained Weight: " << weight << std::endl;
    std::cout << "Trained Bias: " << bias << std::endl;

    return 0;
} 

void trainLinearRegression(const std::vector<double>& x, const std::vector<double>& y, double& weight, double& bias, double learningRate, int epochs) {
    int n = x.size();
    for (int epoch = 0; epoch < epochs; ++epoch) {
        double weightGradient = 0.0;
        double biasGradient = 0.0;
        for (int i = 0; i < n; ++i) {
            double prediction = weight * x[i] + bias;
            double error = prediction - y[i];
            weightGradient += (2.0 / n) * error * x[i];
            biasGradient += (2.0 / n) * error;
        }
        weight -= learningRate * weightGradient;
        bias -= learningRate * biasGradient;
    }
}

int main() {
    std::vector<double> x = {1.0, 2.0, 3.0, 4.0, 5.0};
    std::vector<double> y = {2.0, 4.0, 6.0, 8.0, 10.0};

    double weight = 0.0;
    double bias = 0.0;
    double learningRate = 0.01;
    int epochs = 1000;

    trainLinearRegression(x, y, weight, bias, learningRate, epochs);

    std::cout << "Trained Weight: " << weight << std::endl;
    std::cout << "Trained Bias: " << bias << std::endl;

    return 0;
}
#include <stdexcept>
#include <vector>

class LinearRegression {
private:
    double weight;
    double bias;
    double learning_rate;
    int epochs;

public:
    LinearRegression(double lr = 0.01, int epochs_cnt = 2000)
        : weight(0.0), bias(0.0), learning_rate(lr), epochs(epochs_cnt) {}

    double getWeight() const { return weight; }
    double getBias() const { return bias; }

    static double computeMSE(const std::vector<double>& x, const std::vector<double>& y, double w, double b) {
        if (x.size() != y.size() || x.empty()) {
            throw std::invalid_argument("Input vectors must be non-empty and of equal size.");
        }
        double total_error = 0.0;
        size_t n = x.size();
        for (size_t i = 0; i < n; ++i) {
            double prediction = w * x[i] + b;
            double error = prediction - y[i];
            total_error += error * error;
        }
        return total_error / static_cast<double>(n);
    }

    void fit(const std::vector<double>& x, const std::vector<double>& y) {
        if (x.size() != y.size() || x.empty()) {
            throw std::invalid_argument("Input vectors must be non-empty and of equal size.");
        }
        size_t n = x.size();
        double num_samples = static_cast<double>(n);

        for (int epoch = 0; epoch < epochs; ++epoch) {
            double dw = 0.0;
            double db = 0.0;

            for (size_t i = 0; i < n; ++i) {
                double prediction = weight * x[i] + bias;
                double error = prediction - y[i];
                dw += error * x[i];
                db += error;
            }

            dw = (2.0 / num_samples) * dw;
            db = (2.0 / num_samples) * db;

            weight -= learning_rate * dw;
            bias -= learning_rate * db;
        }
    }

    double predict(double x) const {
        return weight * x + bias;
    }

    std::vector<double> predict(const std::vector<double>& x) const {
        std::vector<double> predictions;
        predictions.reserve(x.size());
        for (double val : x) {
            predictions.push_back(predict(val));
        }
        return predictions;
    }
};

int main() {
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "--- C++ Linear Regression with Gradient Descent ---" << std::endl;

    std::vector<double> x_train = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    std::vector<double> y_train = {3.7, 6.2, 8.7, 11.2, 13.7, 16.2, 18.7, 21.2, 23.7, 26.2};

    LinearRegression model(0.01, 5000);

    std::cout << "Initial MSE: " << LinearRegression::computeMSE(x_train, y_train, 0.0, 0.0) << std::endl;

    model.fit(x_train, y_train);

    std::cout << "Trained Weight: " << model.getWeight() << " (Expected ~2.5)" << std::endl;
    std::cout << "Trained Bias:   " << model.getBias() << " (Expected ~1.2)" << std::endl;

    double final_mse = LinearRegression::computeMSE(x_train, y_train, model.getWeight(), model.getBias());
    std::cout << "Final MSE: " << final_mse << std::endl;

    double test_x = 11.0;
    double predicted_y = model.predict(test_x);
    std::cout << "Prediction for x = " << test_x << ": " << predicted_y << " (Expected ~28.7)" << std::endl;

    return 0;
}
