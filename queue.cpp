#include <iostream>

class Task {
private:
    unsigned int taskNumber;
    unsigned short int priority;

public:
    // Constructor
    Task(unsigned int taskNumber = 0, unsigned short int priority = 0) {
        this->taskNumber = taskNumber;
        this->priority = priority;
    }

    /**
    ************************************************
    name: getTaskNumber
    description: returns the task number
    parameters:
    return type and description: unsigned int - Returns the task number.
    ************************************************
    */
    unsigned int getTaskNumber() const {
        return taskNumber;
    }

    /**
    ************************************************
    name: getPriority
    description: returns the priority of the task
    parameters:
    return type and description: unsigned short int - Returns the task priority.
    ************************************************
    */
    unsigned short int getPriority() const {
        return priority;
    }
};

// Abstract class Queue
class Queue {
public:
    /**
    ************************************************
    name: addTask
    description: adds a task to the queue
    parameters: taskNumber
    taskNumber - the number of the task to add.
    return type and description: none
    ************************************************
    */
    virtual void addTask(int taskNumber) = 0;

    /**
    ************************************************
    name: removeTask
    description: removes the task with the highest priority
    parameters:
    return type and description: none
    ************************************************
    */
    virtual void removeTask() = 0;

    /**
    ************************************************
    name: peekHighestPriorityTask
    description: returns the task with the highest priority
    parameters:
    return type and description: Task - Returns the task with the highest priority.
    ************************************************
    */
    virtual Task peekHighestPriorityTask() const = 0;

    /**
    ************************************************
    name: isEmpty
    description: checks if the queue is empty
    parameters:
    return type and description: bool - Returns true if the queue is empty.
    ************************************************
    */
    virtual bool isEmpty() const = 0;

    /**
    ************************************************
    name: printQueue
    description: prints all tasks in the queue
    parameters:
    return type and description: none
    ************************************************
    */
    virtual void printQueue() const = 0;

    // Destructor
    virtual ~Queue() {}
};

// Priority queue inheriting from general queue
class PriorityQueueArray : public Queue {
private:
    static const int size = 10;
    Task taskArray[size];
    int currentSize = 0;

public:
    // Constructor
    PriorityQueueArray() {
        this->currentSize = 0;
    }

    /**
    ************************************************
    name: addTask
    description: adds a task to the queue with a priority
    parameters: taskNumber, priority
    taskNumber - number of the task to add
    priority - priority of the task to add
    return type and description: none
    ************************************************
    */
    void addTask(int taskNumber, int priority) {
        if (currentSize == size) {
            std::cout << "Queue is full" << std::endl;
            return;
        }

        Task newTask(taskNumber, priority);
        taskArray[currentSize] = newTask;
        currentSize++;
    }

    /**
    ************************************************
    name: addTask
    description: general task addition implementation
    parameters: taskNumber
    taskNumber - the number of the task to add
    return type and description: none
    ************************************************
    */
    void addTask(int taskNumber) override {
        addTask(taskNumber, 0);  // Default priority is 0
    }

    /**
    ************************************************
    name: removeTask
    description: removes the task with the highest priority from the queue
    parameters:
    return type and description: none
    ************************************************
    */
    void removeTask() override {
        if (currentSize == 0) {
            std::cout << "Queue is empty" << std::endl;
            return;
        }

        int highestPriority = taskArray[0].getPriority();
        int highestPriorityIndex = 0;

        for (int i = 1; i < currentSize; i++) {
            if (taskArray[i].getPriority() > highestPriority) {
                highestPriority = taskArray[i].getPriority();
                highestPriorityIndex = i;
            }
        }

        for (int i = highestPriorityIndex; i < currentSize - 1; i++) {
            taskArray[i] = taskArray[i + 1];
        }

        currentSize--;
    }

    /**
    ************************************************
    name: peekHighestPriorityTask
    description: returns the task with the highest priority
    parameters:
    return type and description: Task - Returns the task with the highest priority.
    ************************************************
    */
    Task peekHighestPriorityTask() const override {
        if (currentSize == 0) {
            std::cout << "Queue is empty" << std::endl;
            return Task();  // Returns an empty task
        }

        int highestPriority = taskArray[0].getPriority();
        int highestPriorityIndex = 0;

        for (int i = 1; i < currentSize; i++) {
            if (taskArray[i].getPriority() > highestPriority) {
                highestPriority = taskArray[i].getPriority();
                highestPriorityIndex = i;
            }
        }

        return taskArray[highestPriorityIndex];
    }

    /**
    ************************************************
    name: isEmpty
    description: checks if the queue is empty
    parameters:
    return type and description: bool - Returns true if the queue is empty.
    ************************************************
    */
    bool isEmpty() const override {
        return currentSize == 0;
    }

    /**
    ************************************************
    name: printQueue
    description: prints the contents of the queue
    parameters:
    return type and description: none
    ************************************************
    */
    void printQueue() const override {
        for (int i = 0; i < currentSize; i++) {
            std::cout << "Task number " << taskArray[i].getTaskNumber() << " has priority " << taskArray[i].getPriority() << std::endl;
        }
    }
};

int main() {
    PriorityQueueArray queue;

    // Adding tasks with priorities
    for (int i = 0; i < 10; i++) {
        queue.addTask(i, i % 3);
    }
    queue.printQueue();

    // Removing the task with the highest priority
    std::cout << "\nRemoving the highest priority task:" << std::endl;
    queue.removeTask();
    queue.printQueue();

    // Peeking at the highest priority task
    std::cout << "\nPeeking at the highest priority task:" << std::endl;
    Task highest = queue.peekHighestPriorityTask();
    std::cout << "Task number " << highest.getTaskNumber() << " has priority " << highest.getPriority() << std::endl;

    // Checking if the queue is empty
    std::cout << "Is the queue empty? " << (queue.isEmpty() ? "Yes" : "No") << std::endl;

    return 0;
}
