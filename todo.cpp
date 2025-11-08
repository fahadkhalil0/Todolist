#include <iostream>
#include <string>
using namespace std;

// ==================== MODULE 1: TASK MANAGEMENT (LINKED LIST) ====================

struct Task {
    string name;
    string description;
    string priority;      // High, Medium, Low
    string status;        // Pending, Completed
    string category;      // Work, Personal, etc.
    Task* next;
};

// Create a new task node
Task* createTask(string name, string desc, string priority, string category) {
    Task* newTask = new Task();
    newTask->name = name;
    newTask->description = desc;
    newTask->priority = priority;
    newTask->status = "Pending";
    newTask->category = category;
    newTask->next = nullptr;
    return newTask;
}

// Add task at the end of linked list
void addTask(Task** head, string name, string desc, string priority, string category) {
    Task* newTask = createTask(name, desc, priority, category);
    
    if (*head == nullptr) {
        *head = newTask;
    } else {
        Task* temp = *head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newTask;
    }
    cout << "\n✓ Task added successfully!\n";
}

// Delete task by name
bool deleteTask(Task** head, string name) {
    if (*head == nullptr) {
        cout << "\n✗ No tasks to delete!\n";
        return false;
    }

    // Delete head
    if ((*head)->name == name) {
        Task* temp = *head;
        *head = (*head)->next;
        delete temp;
        cout << "\n✓ Task deleted successfully!\n";
        return true;
    }

    // Delete from middle or end
    Task* current = *head;
    while (current->next != nullptr) {
        if (current->next->name == name) {
            Task* temp = current->next;
            current->next = current->next->next;
            delete temp;
            cout << "\n✓ Task deleted successfully!\n";
            return true;
        }
        current = current->next;
    }

    cout << "\n✗ Task not found!\n";
    return false;
}

// Edit task details
bool editTask(Task* head, string name, string newDesc, string newPriority) {
    Task* current = head;
    while (current != nullptr) {
        if (current->name == name) {
            current->description = newDesc;
            current->priority = newPriority;
            cout << "\n✓ Task updated successfully!\n";
            return true;
        }
        current = current->next;
    }
    cout << "\n✗ Task not found!\n";
    return false;
}

// Mark task as completed
bool markCompleted(Task* head, string name) {
    Task* current = head;
    while (current != nullptr) {
        if (current->name == name) {
            current->status = "Completed";
            cout << "\n✓ Task marked as completed!\n";
            return true;
        }
        current = current->next;
    }
    cout << "\n✗ Task not found!\n";
    return false;
}

// Get total task count
int getTaskCount(Task* head) {
    int count = 0;
    Task* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

// ==================== MODULE 2: UNDO/REDO SYSTEM (STACK) ====================

struct Action {
    string actionType;    // "Add", "Delete", "Edit", "Mark"
    string taskName;
    string taskDesc;
    string taskPriority;
    string taskCategory;
    Action* next;
};

struct ActionStack {
    Action* top;
};

// Create empty stack
ActionStack* createStack() {
    ActionStack* stack = new ActionStack();
    stack->top = nullptr;
    return stack;
}

// Push action onto stack
void push(ActionStack* stack, string type, string name, string desc = "", string priority = "", string category = "") {
    Action* newAction = new Action();
    newAction->actionType = type;
    newAction->taskName = name;
    newAction->taskDesc = desc;
    newAction->taskPriority = priority;
    newAction->taskCategory = category;
    newAction->next = stack->top;
    stack->top = newAction;
}

// Pop action from stack
bool pop(ActionStack* stack) {
    if (stack->top == nullptr) return false;
    Action* temp = stack->top;
    stack->top = stack->top->next;
    delete temp;
    return true;
}

// Check if stack is empty
bool isStackEmpty(ActionStack* stack) {
    return stack->top == nullptr;
}

// Display action history
void displayHistory(ActionStack* stack) {
    if (isStackEmpty(stack)) {
        cout << "\n✗ No action history!\n";
        return;
    }
    cout << "\n--- Action History (Most Recent First) ---\n";
    Action* current = stack->top;
    int count = 1;
    while (current != nullptr) {
        cout << count << ". " << current->actionType << ": " << current->taskName << endl;
        current = current->next;
        count++;
    }
}

// Get top action without removing
Action* peekStack(ActionStack* stack) {
    if (isStackEmpty(stack)) return nullptr;
    return stack->top;
}

// Delete entire stack
void deleteStack(ActionStack** stack) {
    while (!isStackEmpty(*stack)) {
        pop(*stack);
    }
    delete *stack;
    *stack = nullptr;
}

// ==================== MODULE 3: RECURSIVE SEARCH/FILTER ====================

// Recursive search by name
Task* searchByName(Task* current, string keyword) {
    // Base case: reached end of list
    if (current == nullptr) {
        return nullptr;
    }
    
    // Check if keyword matches
    if (current->name.find(keyword) != string::npos) {
        return current;
    }
    
    // Recursive case: search in next node
    return searchByName(current->next, keyword);
}

// Recursive filter by status
void filterByStatus(Task* current, string status) {
    // Base case
    if (current == nullptr) {
        return;
    }
    
    // Process current task
    if (current->status == status) {
        cout << "  • " << current->name << " [" << current->priority << "] - " 
             << current->status << endl;
    }
    
    // Recursive case
    filterByStatus(current->next, status);
}

// Recursive filter by priority
void filterByPriority(Task* current, string priority) {
    // Base case
    if (current == nullptr) {
        return;
    }
    
    // Process current task
    if (current->priority == priority) {
        cout << "  • " << current->name << " [" << current->priority << "] - " 
             << current->status << endl;
    }
    
    // Recursive case
    filterByPriority(current->next, priority);
}

// Recursive display in reverse
void displayReverse(Task* current) {
    // Base case: reached end
    if (current == nullptr) {
        return;
    }
    
    // Recursive case: go to next first
    displayReverse(current->next);
    
    // Then print current (after recursion unwinds)
    cout << "  • " << current->name << " - " << current->status << endl;
}

// Recursive count tasks
int countTasks(Task* current) {
    // Base case
    if (current == nullptr) {
        return 0;
    }
    
    // Recursive case: 1 + count of remaining
    return 1 + countTasks(current->next);
}

// Recursive count completed tasks
int countCompleted(Task* current) {
    // Base case
    if (current == nullptr) {
        return 0;
    }
    
    // Check if current is completed
    int count = (current->status == "Completed") ? 1 : 0;
    
    // Recursive case
    return count + countCompleted(current->next);
}

// ==================== MODULE 4: DISPLAY & SORTING ====================

// Display all tasks
void displayAllTasks(Task* head) {
    if (head == nullptr) {
        cout << "\n✗ No tasks yet!\n";
        return;
    }
    cout << "\n========== ALL TASKS ==========\n";
    Task* current = head;
    int count = 1;
    while (current != nullptr) {
        cout << count << ". " << current->name << endl;
        cout << "   Description: " << current->description << endl;
        cout << "   Priority: " << current->priority << " | Status: " << current->status << endl;
        cout << "   Category: " << current->category << endl;
        cout << "---\n";
        current = current->next;
        count++;
    }
}

// Display tasks in reverse order (using recursion)
void displayReverseTasks(Task* head) {
    if (head == nullptr) {
        cout << "\n✗ No tasks yet!\n";
        return;
    }
    cout << "\n========== TASKS IN REVERSE ORDER ==========\n";
    displayReverse(head);
}

// Display by priority
void displayByPriority(Task* head, string priority) {
    cout << "\n========== TASKS WITH " << priority << " PRIORITY ==========\n";
    filterByPriority(head, priority);
}

// Display summary statistics
void displaySummary(Task* head) {
    int total = countTasks(head);
    int completed = countCompleted(head);
    int pending = total - completed;

    cout << "\n========== TASK SUMMARY ==========\n";
    cout << "Total Tasks: " << total << endl;
    cout << "Completed: " << completed << endl;
    cout << "Pending: " << pending << endl;
    if (total > 0) {
        cout << "Completion Rate: " << (completed * 100 / total) << "%" << endl;
    }
}

// ==================== MODULE 5: USER INTERFACE / MENU SYSTEM ====================

void displayMainMenu() {
    cout << "\n====== SUPERCHARGED TO-DO LIST ======\n";
    cout << "1. Add Task\n";
    cout << "2. Delete Task\n";
    cout << "3. Edit Task\n";
    cout << "4. Mark Task as Completed\n";
    cout << "5. Search Task\n";
    cout << "6. Filter Tasks\n";
    cout << "7. Display All Tasks\n";
    cout << "8. Display Tasks in Reverse\n";
    cout << "9. Show Summary\n";
    cout << "10. View Action History\n";
    cout << "11. Exit\n";
    cout << "=====================================\n";
}

void addTaskMenu(Task** head, ActionStack* stack) {
    cout << "\n--- Add New Task ---\n";
    string name, desc, priority, category;
    
    cout << "Task Name: ";
    getline(cin, name);
    
    cout << "Description: ";
    getline(cin, desc);
    
    cout << "Priority (High/Medium/Low): ";
    getline(cin, priority);
    
    cout << "Category (Work/Personal/Other): ";
    getline(cin, category);

    addTask(head, name, desc, priority, category);
    push(stack, "Add", name, desc, priority, category);
}

void deleteTaskMenu(Task** head, ActionStack* stack) {
    cout << "\n--- Delete Task ---\n";
    displayAllTasks(*head);
    
    if (getTaskCount(*head) == 0) return;
    
    string name;
    cout << "Enter task name to delete: ";
    getline(cin, name);
    
    if (deleteTask(head, name)) {
        push(stack, "Delete", name);
    }
}

void editTaskMenu(Task* head, ActionStack* stack) {
    cout << "\n--- Edit Task ---\n";
    displayAllTasks(head);
    
    if (getTaskCount(head) == 0) return;
    
    string name, desc, priority;
    cout << "Enter task name to edit: ";
    getline(cin, name);
    
    cout << "New description: ";
    getline(cin, desc);
    
    cout << "New priority (High/Medium/Low): ";
    getline(cin, priority);
    
    if (editTask(head, name, desc, priority)) {
        push(stack, "Edit", name, desc, priority);
    }
}

void markCompletedMenu(Task* head, ActionStack* stack) {
    cout << "\n--- Mark Task as Completed ---\n";
    displayAllTasks(head);
    
    if (getTaskCount(head) == 0) return;
    
    string name;
    cout << "Enter task name to mark as completed: ";
    getline(cin, name);
    
    if (markCompleted(head, name)) {
        push(stack, "Mark", name);
    }
}

void searchTaskMenu(Task* head) {
    cout << "\n--- Search Task ---\n";
    string keyword;
    cout << "Enter task name to search: ";
    getline(cin, keyword);
    
    Task* found = searchByName(head, keyword);
    if (found != nullptr) {
        cout << "\n✓ Task Found!\n";
        cout << "Name: " << found->name << endl;
        cout << "Description: " << found->description << endl;
        cout << "Priority: " << found->priority << " | Status: " << found->status << endl;
    } else {
        cout << "\n✗ Task not found!\n";
    }
}

void filterTasksMenu(Task* head) {
    cout << "\n--- Filter Tasks ---\n";
    cout << "1. Filter by Status\n";
    cout << "2. Filter by Priority\n";
    int choice;
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        string status;
        cout << "Enter status (Pending/Completed): ";
        getline(cin, status);
        cout << "\nTasks with status: " << status << "\n";
        filterByStatus(head, status);
    } else if (choice == 2) {
        string priority;
        cout << "Enter priority (High/Medium/Low): ";
        getline(cin, priority);
        displayByPriority(head, priority);
    }
}

void exitConfirmation() {
    cout << "\nAre you sure you want to exit? (yes/no): ";
    string confirm;
    getline(cin, confirm);
    if (confirm == "yes") {
        cout << "\nThank you for using Supercharged To-Do List!\n";
    }
}

// Delete entire task list
void deleteAllTasks(Task** head) {
    while (*head != nullptr) {
        Task* temp = *head;
        *head = (*head)->next;
        delete temp;
    }
}

// ==================== MAIN FUNCTION ====================

int main() {
    Task* head = nullptr;
    ActionStack* undoStack = createStack();
    
    int choice;
    bool running = true;
    
    while (running) {
        displayMainMenu();
        cout << "\nEnter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addTaskMenu(&head, undoStack);
                break;
            case 2:
                deleteTaskMenu(&head, undoStack);
                break;
            case 3:
                editTaskMenu(head, undoStack);
                break;
            case 4:
                markCompletedMenu(head, undoStack);
                break;
            case 5:
                searchTaskMenu(head);
                break;
            case 6:
                filterTasksMenu(head);
                break;
            case 7:
                displayAllTasks(head);
                break;
            case 8:
                displayReverseTasks(head);
                break;
            case 9:
                displaySummary(head);
                break;
            case 10:
                displayHistory(undoStack);
                break;
            case 11:
                exitConfirmation();
                running = false;
                break;
            default:
                cout << "\n✗ Invalid choice! Please try again.\n";
        }
    }
    
    // Cleanup memory
    deleteAllTasks(&head);
    deleteStack(&undoStack);
    
    return 0;
}