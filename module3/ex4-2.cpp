#include <array>
#include <set>
#include <iostream>
#include <stdlib.h>
#include <unordered_map>
#include <algorithm>

const int SIDE_SIZE = 4;
const int FIELD_SIZE = 16;
const std::array<int, FIELD_SIZE> finalField = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};

class Puzzle {
public:
    Puzzle(std::array<int, FIELD_SIZE> field)
            : field(field) {
        emptyPos = -1;
        for (int i = 0; i < FIELD_SIZE; i++) {
            if (field[i] == 0)
                emptyPos = i;
        }
    }

    Puzzle(Puzzle const &other)
            : field(other.field),
              emptyPos(other.emptyPos) {
    }

    bool IsComplete() {
        return field == finalField;
    }

    bool CanMoveLeft() {
        return emptyPos % SIDE_SIZE != SIDE_SIZE - 1;
    }

    bool CanMoveRight() {
        return emptyPos % SIDE_SIZE != 0;
    }

    bool CanMoveUp() {
        return emptyPos < FIELD_SIZE - SIDE_SIZE;
    }

    bool CanMoveDown() {
        return emptyPos > SIDE_SIZE - 1;
    }

    Puzzle MoveLeft() {
        Puzzle newPuzzle(*this);
        std::swap(newPuzzle.field[emptyPos], newPuzzle.field[emptyPos + 1]);
        newPuzzle.emptyPos++;
        return newPuzzle;
    }

    Puzzle MoveRight() {
        Puzzle newPuzzle(*this);
        std::swap(newPuzzle.field[emptyPos], newPuzzle.field[emptyPos - 1]);
        newPuzzle.emptyPos--;
        return newPuzzle;
    }

    Puzzle MoveUp() {
        Puzzle newPuzzle(*this);
        std::swap(newPuzzle.field[emptyPos], newPuzzle.field[emptyPos + SIDE_SIZE]);
        newPuzzle.emptyPos += SIDE_SIZE;
        return newPuzzle;
    }

    Puzzle MoveDown() {
        Puzzle newPuzzle(*this);
        std::swap(newPuzzle.field[emptyPos], newPuzzle.field[emptyPos - SIDE_SIZE]);
        newPuzzle.emptyPos -= SIDE_SIZE;
        return newPuzzle;
    }

    bool IsSolvable() {
        int inversions = 0;
        for (int i = 0; i < FIELD_SIZE; i++)
            for (int j = i + 1; j < FIELD_SIZE; j++)
                if (field[i] != 0 && field[j] != 0 && field[i] > field[j])
                    inversions++;
        return (inversions % 2 == 0) == (emptyPos / 4 % 2 == 1);
    }

    int heuristic(Puzzle futurePuzzle) {
        std::array<int, FIELD_SIZE> futureField = futurePuzzle.field;
        int h = 0;
        for (int i = 0; i < FIELD_SIZE; i++) { // проходим по всем костяшкам
            if (futureField[i] == 0) // пропускаем пустую костяшку
                continue;
            if (i != futureField[i] - 1) { // если костяшка стоит не на своем месте
                int moving = abs(i / FIELD_SIZE - (futureField[i] - 1) / FIELD_SIZE) // перемещние по вертикали
                             + abs(i % FIELD_SIZE - (futureField[i] - 1) % FIELD_SIZE); // перемещение по горизонтали
                h += moving; // добавляем в эвристику число ходов для постановкии костяшки на место
            }
        }
        return h;
    }

    /*int heuristic(Puzzle futurePuzzle) {
        std::array<int, FIELD_SIZE> futureField = futurePuzzle.field;
        int h = 0;
        for (int i = 0; i < FIELD_SIZE; i++) { // проходим по всем костяшкам
            if (futureField[i] != finalField[i])
                h += 1;
        }
        return h;
    }*/

    int transform(std::array<int, FIELD_SIZE> field) {
        int t = 0;
        for (int i = 0; i < FIELD_SIZE; i++) {
            t += (i + 1) * field[i];
        }
        return t;
    }

    std::string SolveAStar(std::array<int, FIELD_SIZE> field) {

        Puzzle startState(field);

        std::set<std::pair<int, Puzzle> > priority_queue;
        priority_queue.insert(std::pair<int, Puzzle>(0, startState));

        std::unordered_map<int, char> visited;
        visited[transform(startState.field)] = 'S';

        while (true) { // построение графа решений
            int depth = 0;
            Puzzle curState = startState;
            if ( !priority_queue.empty()) {
                curState = (priority_queue.begin())->second;
                depth = (priority_queue.begin())->first - heuristic(curState);
                priority_queue.erase(priority_queue.begin());
            }

            if (curState.IsComplete())
                break;

            if (curState.CanMoveLeft()) {
                std::cout << "Left" << std::endl;
                Puzzle newState = curState.MoveLeft();
                if (visited.find(transform(newState.field)) == visited.end()) { // если такого состояния еще не было
                    priority_queue.insert(std::pair<int, Puzzle>(depth + 1 + heuristic(newState), newState));
                    visited[transform(newState.field)] = 'L';
                }
                std::cout << newState << std::endl;
            }

            if (curState.CanMoveRight()) {
                std::cout << "Right" << std::endl;
                Puzzle newState = curState.MoveRight();
                if (visited.find(transform(newState.field)) == visited.end()) { // если такого состояния еще не было
                    priority_queue.insert(std::pair<int, Puzzle>(depth + 1 + heuristic(newState), newState));
                    visited[transform(newState.field)] = 'R';
                }
                std::cout << newState << std::endl;
            }

            if (curState.CanMoveUp()) {
                std::cout << "Up" << std::endl;
                Puzzle newState = curState.MoveUp();
                if (visited.find(transform(newState.field)) == visited.end()) { // если такого состояния еще не было
                    priority_queue.insert(std::pair<int, Puzzle>(depth + 1 + heuristic(newState), newState));
                    visited[transform(newState.field)] = 'U';
                }
                std::cout << newState << std::endl;
            }

            if (curState.CanMoveDown()) {
                std::cout << "Down" << std::endl;
                Puzzle newState = curState.MoveDown();
                if (visited.find(transform(newState.field)) == visited.end()) { // если такого состояния еще не было
                    priority_queue.insert(std::pair<int, Puzzle>(depth + 1 + heuristic(newState), newState));
                    visited[transform(newState.field)] = 'D';
                }
                std::cout << newState << std::endl;
            }
            //std::cout << curState << std::endl;
        }

        std::string path; // поиск пути
        Puzzle state(finalField);
        while (visited[transform(state.field)] != 'S') {
            char move = visited[transform(state.field)];
            switch (move) {
                case 'L':
                    path += 'L';
                    state = state.MoveRight();
                    break;
                case 'R':
                    path += 'R';
                    state = state.MoveLeft();
                    break;
                case 'U':
                    path += 'U';
                    state = state.MoveDown();
                    break;
                case 'D':
                    path += 'D';
                    state = state.MoveUp();
                    break;
            }
        }

        std::reverse(path.begin(), path.end());
        return path;
    }

    friend std::ostream& operator<<(std::ostream &out, const Puzzle &state);
    friend bool operator<(const Puzzle &L, const Puzzle &R) { return true; };
    std::array<int, FIELD_SIZE> field;
private:
    //std::array<int, FIELD_SIZE> field;
    int emptyPos;
};

std::ostream& operator<<(std::ostream &out, const Puzzle &state) {
    for (int i = 0; i < SIDE_SIZE; i++) {
        for (int j = 0; j < SIDE_SIZE; j++) {
            out << state.field[i * SIDE_SIZE + j] << " ";
        }
        out << std::endl;
    }
    return out;
}


int main() {
    std::ios::sync_with_stdio(false); // оптимизация ввода

    std::array<int, FIELD_SIZE> field;
    for (int i = 0; i < FIELD_SIZE; i++) { // ввод поля
        std::cin >> field[i];
    }
    Puzzle game(field);
    if (game.IsSolvable()) {
        std::string path = game.SolveAStar(field);
        std::cout << path.length() << std::endl; // вывод количсетва ходов
        std::cout << path << std::endl; // вывод ходов
    }
    else
        std::cout << "-1" << std::endl;
    return 0;
}