#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Observer Interface
class HealthObserver {
public:
    virtual void update(int steps, int caloriesBurned) = 0;
    virtual void waterReminder() = 0;
    virtual void dietReminder() = 0;
};

// Concrete Observer - MobileApp
class MobileApp : public HealthObserver {
public:
    void update(int steps, int caloriesBurned) override {
        cout << "Mobile App: You've taken " << steps << " steps today. Keep it up!" << endl;
    }

    void waterReminder() override {
        cout << "Mobile App: Reminder - Stay hydrated! Drink water." << endl;
    }

    void dietReminder() override {
        cout << "Mobile App: Reminder - Consider having a healthy meal to refuel your energy." << endl;
    }
};

// Singleton Pattern - Pedometer
class Pedometer {
private:
    static Pedometer* instance;
    vector<HealthObserver*> observers;
    int totalSteps;
    int totalCaloriesBurned;

    Pedometer() : totalSteps(0), totalCaloriesBurned(0) {}

public:
    static Pedometer* getInstance() {
        if (!instance) {
            instance = new Pedometer();
        }
        return instance;
    }

    void addObserver(HealthObserver* observer) {
        observers.push_back(observer);
    }

    void removeObserver(HealthObserver* observer) {
        // Implementation can be added if needed
    }

    void notifyObservers() {
        for (const auto& observer : observers) {
            observer->update(totalSteps, totalCaloriesBurned);
        }
    }

    void notifyWaterReminder() {
        for (const auto& observer : observers) {
            observer->waterReminder();
        }
    }

    void notifyDietReminder() {
        for (const auto& observer : observers) {
            observer->dietReminder();
        }
    }

    void recordSteps(int steps, int caloriesBurned) {
        totalSteps += steps;
        totalCaloriesBurned += caloriesBurned;
        notifyObservers();

        // Simulate reminders based on total steps and calories burned
        if (totalSteps > 5000) {
            notifyWaterReminder();
        }
        if (totalCaloriesBurned > 300) {
            notifyDietReminder();
        }
    }
};

Pedometer* Pedometer::instance = nullptr;

// Factory Method Pattern - ExerciseFactory
class Activity {
public:
    string name;
    int duration;
    int caloriesBurned;

    Activity(const string& _name, int _duration, int _caloriesBurned)
        : name(_name), duration(_duration), caloriesBurned(_caloriesBurned) {}
};

class ExerciseFactory {
public:
    virtual Activity createExercise() = 0;
};

class RunningFactory : public ExerciseFactory {
public:
    Activity createExercise() override {
        return Activity("Running", 30, 200);
    }
};

class WeightliftingFactory : public ExerciseFactory {
public:
    Activity createExercise() override {
        return Activity("Weightlifting", 45, 150);
    }
};

// MVC Pattern
class HealthTrackerModel {
private:
    vector<Activity> activities;
    Pedometer* pedometer;

public:
    HealthTrackerModel(Pedometer* _pedometer) : pedometer(_pedometer) {}

    void recordActivity(const Activity& activity) {
        activities.push_back(activity);
        cout << "Activity recorded: " << activity.name << ", Duration: " << activity.duration
            << " minutes, Calories Burned: " << activity.caloriesBurned << endl;
        pedometer->recordSteps(500, activity.caloriesBurned); // Simulate steps recording
    }

    int calculateTotalCalories() const {
        int totalCalories = 0;
        for (const auto& activity : activities) {
            totalCalories += activity.caloriesBurned;
        }
        return totalCalories;
    }
};

class HealthTrackerView {
public:
    void displayHealthReport(int totalCaloriesBurned, int waterConsumed) const {
        cout << "\n--- Health Report ---" << endl;
        cout << "Total Calories Burned: " << totalCaloriesBurned << " calories" << endl;
        cout << "Water Consumed: " << waterConsumed << " ml" << endl;
        cout << "---------------------\n" << endl;
    }
};

class HealthTrackerController {
private:
    HealthTrackerModel* model;
    HealthTrackerView* view;

public:
    HealthTrackerController(HealthTrackerModel* _model, HealthTrackerView* _view)
        : model(_model), view(_view) {}

    void recordActivity(const Activity& activity) {
        model->recordActivity(activity);
        view->displayHealthReport(model->calculateTotalCalories(), 1000); // Simulate water consumption
    }
};

int main() {
    Pedometer* pedometer = Pedometer::getInstance();

    MobileApp mobileApp;
    pedometer->addObserver(&mobileApp);

    HealthTrackerModel model(pedometer);
    HealthTrackerView view;
    HealthTrackerController controller(&model, &view);

    char choice;
    do {
        cout << "Choose an activity (R for Running, W for Weightlifting, Q to Quit): ";
        cin >> choice;

        ExerciseFactory* exerciseFactory = nullptr;

        switch (choice) {
        case 'R':
        case 'r':
            exerciseFactory = new RunningFactory();
            break;
        case 'W':
        case 'w':
            exerciseFactory = new WeightliftingFactory();
            break;
        case 'Q':
        case 'q':
            cout << "Quitting the program." << endl;
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
            continue;
        }

        if (exerciseFactory) {
            Activity exercise = exerciseFactory->createExercise();
            controller.recordActivity(exercise);
            delete exerciseFactory;
        }

    } while (choice != 'Q' && choice != 'q');

    return 0;
}
