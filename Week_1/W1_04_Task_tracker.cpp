#include <iostream>
#include <map>
#include <string>
#include <tuple>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
    NEW,         // новая
    IN_PROGRESS, // в разработке
    TESTING,     // на тестировании
    DONE         // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo &GetPersonTasksInfo(const string &person) const {
        return database.at(person);
    };

    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string &person) {
        ++database[person][TaskStatus::NEW];
    };

    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo>
    PerformPersonTasks(const string &person, int task_count) {
        TasksInfo updated_tsk, untouched_tsk;
        if (database.count(person) != 1) { // случай когда нет задач у конкретного разработчика
            return tie(updated_tsk, untouched_tsk);
        }

        int a = 0, b = 0, c = 0, d = 0, k = 0;
        tie(a, b, c, d) = CountUncomplitTasks(GetPersonTasksInfo(person));
        int cnt = a + b + c;
        if (task_count > cnt) {
            task_count = cnt; // task_count не может быть больше суммы a + b + c.
        }

        if (a == 0 && b == 0 && c == 0) { // ==== это случай NEW = 0, IN_PROGRESS = 0, TESTING = 0
            return tie(updated_tsk, untouched_tsk);
        } else if (a != 0 && b == 0 && c == 0) { // ==== это случай NEW != 0, IN_PROGRESS:0, TESTING:0
            if (task_count == a) {
                database[person].erase(TaskStatus::NEW);
            } else {
                database[person][TaskStatus::NEW] = a - task_count;
                untouched_tsk[TaskStatus::NEW] = a - task_count;
            }
            updated_tsk[TaskStatus::IN_PROGRESS] = task_count;
            database[person][TaskStatus::IN_PROGRESS] = task_count;

            return tie(updated_tsk, untouched_tsk);
        } else if (a == 0 && b != 0 && c == 0) { // ==== это случай NEW = 0, IN_PROGRESS != 0, TESTING = 0
            if (task_count == b) {
                database[person].erase(TaskStatus::IN_PROGRESS);
            } else {
                database[person][TaskStatus::IN_PROGRESS] = b - task_count;
                untouched_tsk[TaskStatus::IN_PROGRESS] = b - task_count;
            }
            updated_tsk[TaskStatus::TESTING] = task_count;
            database[person][TaskStatus::TESTING] = task_count;

            return tie(updated_tsk, untouched_tsk);
        } else if (a == 0 && b == 0 && c != 0) { // ==== это случай NEW = 0, IN_PROGRESS = 0, TESTING != 0
            if (task_count == c) {
                database[person].erase(TaskStatus::TESTING);
            } else {
                database[person][TaskStatus::TESTING] = c - task_count;
                untouched_tsk[TaskStatus::TESTING] = c - task_count;
            }
            updated_tsk[TaskStatus::DONE] = task_count;
            database[person][TaskStatus::DONE] += task_count;

            return tie(updated_tsk, untouched_tsk);
        } else if (a != 0 && b == 0 && c != 0) { // ==== это случай NEW != 0, IN_PROGRESS = 0, TESTING != 0 
            if (task_count == a) {
                database[person].erase(TaskStatus::NEW);
                database[person][TaskStatus::IN_PROGRESS] = task_count;
                updated_tsk[TaskStatus::IN_PROGRESS] = task_count;
                untouched_tsk[TaskStatus::TESTING] = c;

                return tie(updated_tsk, untouched_tsk);
            } else if (task_count < a) {
                database[person][TaskStatus::NEW] = a - task_count;
                untouched_tsk[TaskStatus::NEW] = a - task_count;
                database[person][TaskStatus::IN_PROGRESS] = task_count;
                updated_tsk[TaskStatus::IN_PROGRESS] = task_count;
                untouched_tsk[TaskStatus::TESTING] = c;

                return tie(updated_tsk, untouched_tsk);
            } else if (task_count > a) {
                database[person].erase(TaskStatus::NEW);
                database[person][TaskStatus::IN_PROGRESS] = a;
                updated_tsk[TaskStatus::IN_PROGRESS] = a;

                task_count -= a;

                if (task_count == c) {
                    database[person].erase(TaskStatus::TESTING);
                } else {
                    database[person][TaskStatus::TESTING] = c - task_count;
                    untouched_tsk[TaskStatus::TESTING] = c - task_count;
                }

                updated_tsk[TaskStatus::DONE] = task_count;
                database[person][TaskStatus::DONE] += task_count;
                return tie(updated_tsk, untouched_tsk);
            }
        } else if (a == 0 && b != 0 && c != 0) { // ==== это случай NEW = 0, IN_PROGRESS != 0, TESTING != 0
            if (task_count == b) {
                database[person].erase(TaskStatus::IN_PROGRESS);
                database[person][TaskStatus::TESTING] += task_count;
                updated_tsk[TaskStatus::TESTING] = task_count;
                untouched_tsk[TaskStatus::TESTING] = c;

                return tie(updated_tsk, untouched_tsk);
            } else if (task_count < b) {
                database[person][TaskStatus::IN_PROGRESS] = b - task_count;
                untouched_tsk[TaskStatus::IN_PROGRESS] = b - task_count;
                database[person][TaskStatus::TESTING] += task_count;
                updated_tsk[TaskStatus::TESTING] = task_count;
                untouched_tsk[TaskStatus::TESTING] = c;

                return tie(updated_tsk, untouched_tsk);
            } else if (task_count > b) {
                database[person].erase(TaskStatus::IN_PROGRESS);

                task_count -= b;

                database[person][TaskStatus::TESTING] = c - task_count + b;
                updated_tsk[TaskStatus::TESTING] = b;
                if (task_count != c) {
                    untouched_tsk[TaskStatus::TESTING] = c - task_count;
                }

                updated_tsk[TaskStatus::DONE] = task_count;
                database[person][TaskStatus::DONE] += task_count;
                return tie(updated_tsk, untouched_tsk);
            }
        } else if (a != 0 && b != 0 && c == 0) { // ==== это случай NEW != 0, IN_PROGRESS != 0, TESTING = 0
            if (task_count == a) {
                database[person].erase(TaskStatus::NEW);
                database[person][TaskStatus::IN_PROGRESS] += task_count;
                updated_tsk[TaskStatus::IN_PROGRESS] = task_count;
                untouched_tsk[TaskStatus::IN_PROGRESS] = b;

                return tie(updated_tsk, untouched_tsk);
            } else if (task_count < a) {
                database[person][TaskStatus::NEW] = a - task_count;
                untouched_tsk[TaskStatus::NEW] = a - task_count;
                database[person][TaskStatus::IN_PROGRESS] += task_count;
                updated_tsk[TaskStatus::IN_PROGRESS] = task_count;
                untouched_tsk[TaskStatus::IN_PROGRESS] = b;

                return tie(updated_tsk, untouched_tsk);
            } else if (task_count > a) {
                database[person].erase(TaskStatus::NEW);

                task_count -= a;

                database[person][TaskStatus::IN_PROGRESS] = b - task_count + a;
                updated_tsk[TaskStatus::IN_PROGRESS] = a;
                if (task_count != b) {
                    untouched_tsk[TaskStatus::IN_PROGRESS] = b - task_count;
                }

                updated_tsk[TaskStatus::TESTING] = task_count;
                database[person][TaskStatus::TESTING] = task_count;
                return tie(updated_tsk, untouched_tsk);
            }
        } else if (a != 0 && b != 0 && c != 0) { // ==== это случай NEW != 0, IN_PROGRESS != 0, TESTING != 0
            if (task_count == a) {
                database[person].erase(TaskStatus::NEW);
                database[person][TaskStatus::IN_PROGRESS] += task_count;
                updated_tsk[TaskStatus::IN_PROGRESS] = task_count;
                untouched_tsk[TaskStatus::IN_PROGRESS] = b;
                untouched_tsk[TaskStatus::TESTING] = c;

                return tie(updated_tsk, untouched_tsk);
            } else if (task_count < a) {
                database[person][TaskStatus::NEW] = a - task_count;
                untouched_tsk[TaskStatus::NEW] = a - task_count;
                database[person][TaskStatus::IN_PROGRESS] += task_count;
                updated_tsk[TaskStatus::IN_PROGRESS] = task_count;
                untouched_tsk[TaskStatus::IN_PROGRESS] = b;
                untouched_tsk[TaskStatus::TESTING] = c;

                return tie(updated_tsk, untouched_tsk);
            } else if (task_count > a) {
                database[person].erase(TaskStatus::NEW);

                task_count -= a;

                if (task_count == b) {
                    database[person][TaskStatus::IN_PROGRESS] = a;
                    updated_tsk[TaskStatus::IN_PROGRESS] = a;
                    database[person][TaskStatus::TESTING] += task_count;
                    updated_tsk[TaskStatus::TESTING] = task_count;
                    untouched_tsk[TaskStatus::TESTING] = c;

                    return tie(updated_tsk, untouched_tsk);
                } else if (task_count < b) {
                    database[person][TaskStatus::IN_PROGRESS] = b + a - task_count;
                    updated_tsk[TaskStatus::IN_PROGRESS] = a;
                    untouched_tsk[TaskStatus::IN_PROGRESS] = b - task_count;
                    database[person][TaskStatus::TESTING] += task_count;
                    updated_tsk[TaskStatus::TESTING] = task_count;
                    untouched_tsk[TaskStatus::TESTING] = c;

                    return tie(updated_tsk, untouched_tsk);
                } else if (task_count > b) {
                    database[person][TaskStatus::IN_PROGRESS] = a;
                    updated_tsk[TaskStatus::IN_PROGRESS] = a;

                    task_count -= b;

                    database[person][TaskStatus::TESTING] = c - task_count + b;
                    updated_tsk[TaskStatus::TESTING] = b;
                    if (task_count != c) {
                        untouched_tsk[TaskStatus::TESTING] = c - task_count;
                    }

                    updated_tsk[TaskStatus::DONE] = task_count;
                    database[person][TaskStatus::DONE] += task_count;
                    return tie(updated_tsk, untouched_tsk);
                }
            }
        }
    };

private:
    map<string, TasksInfo> database;

    tuple<int, int, int, int> CountUncomplitTasks(const TasksInfo &ts) {
        int n = 0, i = 0, t = 0, d = 0;
        if (ts.count(TaskStatus::NEW) == 1) {
            n = ts.at(TaskStatus::NEW);
        }
        if (ts.count(TaskStatus::IN_PROGRESS) == 1) {
            i = ts.at(TaskStatus::IN_PROGRESS);
        }
        if (ts.count(TaskStatus::TESTING) == 1) {
            t = ts.at(TaskStatus::TESTING);
        }
        if (ts.count(TaskStatus::DONE) == 1) {
            d = ts.at(TaskStatus::DONE);
        }
        return tie(n, i, t, d);
    }
};


// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks"
         << ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress"
         << ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested"
         << ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
    TeamTasks tasks;

/*	tasks.AddNewTask("Ilia");
	for (int i = 0; i < 3; ++i) {
		tasks.AddNewTask("Ivan");
	}
	cout << "Ilia's tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));

	cout << "Ivan's tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
	cout << "\n";

	TasksInfo updated_tasks, untouched_tasks;

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
	cout << "Updated Ivan's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Ivan's tasks: ";
	PrintTasksInfo(untouched_tasks);
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
	cout << "\n";

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
	cout << "Updated Ivan's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Ivan's tasks: ";
	PrintTasksInfo(untouched_tasks);
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
	cout << "\n";

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
	cout << "Updated Ivan's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Ivan's tasks: ";
	PrintTasksInfo(untouched_tasks);
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
	cout << "\n";
	
	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
	cout << "Updated Ivan's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Ivan's tasks: ";
	PrintTasksInfo(untouched_tasks);
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
	cout << "\n";
	
	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
	cout << "Updated Ivan's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Ivan's tasks: ";
	PrintTasksInfo(untouched_tasks);
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
	cout << "\n";


	for (int i = 0; i < 5; ++i) {
		tasks.AddNewTask("Alice");
	}
	cout << "Alice's tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
	cout << "\n";
	
	TasksInfo updated_tasks, untouched_tasks;

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
	cout << "Updated Alice's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Alice's tasks: ";
	PrintTasksInfo(untouched_tasks);
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
	cout << "\n";
	
	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
	cout << "Updated Alice's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Alice's tasks: ";
	PrintTasksInfo(untouched_tasks);
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
	cout << "\n";
	
	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 1);
	cout << "Updated Alice's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Alice's tasks: ";
	PrintTasksInfo(untouched_tasks);
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
	cout << "\n";
	
	
	for (int i = 0; i < 5; ++i) {
		tasks.AddNewTask("Alice");
	}
	cout << "Alice's tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
	cout << "\n";
	
	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 2);
	cout << "Updated Alice's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Alice's tasks: ";
	PrintTasksInfo(untouched_tasks);
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
	cout << "\n";
*/


    tasks.AddNewTask("Ivan");
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
    cout << "\n";

    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
    cout << "\n";

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
    cout << "\n";

    tasks.AddNewTask("Ivan");
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
    cout << "\n";

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
    cout << "\n";

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
    cout << "\n";

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
    cout << "\n";

    return 0;
}