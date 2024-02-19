# Health Tracker

Health Tracker is a C++ application designed to help users monitor their daily physical activities and maintain a healthy lifestyle. It provides features such as activity tracking, calorie counting, hydration reminders, and diet suggestions.

## Features

- **Activity Tracking**: Users can record various physical activities such as running and weightlifting, including the duration and calories burned during each activity session.
  
- **Calorie Counting**: The application calculates the total calories burned based on the recorded activities, allowing users to keep track of their daily calorie expenditure.

- **Hydration Reminders**: Health Tracker reminds users to stay hydrated by sending water consumption reminders based on the total number of steps taken during the day.

- **Diet Suggestions**: Users receive diet reminders suggesting healthy meal options to replenish energy based on the total calories burned throughout the day.

## Design Patterns Used

- **Observer Pattern**: Implemented for notifying the mobile app (observer) about changes in the user's activity data.
  
- **Singleton Pattern**: Used to ensure that only one instance of the Pedometer class exists throughout the application.

- **Factory Method Pattern**: Implemented to create different types of exercises (e.g., running, weightlifting) with a common interface.

- **Model-View-Controller (MVC) Pattern**: Separates the application into three interconnected components: Model (data and business logic), View (presentation layer), and Controller (handles user input and interactions).

## How to Use

1. Run the program.
2. Choose an activity by typing 'R' for running, 'W' for weightlifting, or 'Q' to quit.
3. Follow the prompts to record your activity details.
4. Receive feedback on your total calories burned and water consumption.

## Dependencies

- C++ Standard Library

## Contributing

Contributions are welcome! If you find any bugs or have suggestions for improvements, please feel free to open an issue or submit a pull request.

