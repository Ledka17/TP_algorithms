#include <array>
#include <map>
#include <iostream>
#include <stdlib.h>
#include <unordered_map>

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

    class MyHash {
    public:
        size_t operator()(const Puzzle &state) const {
            size_t hash = 0;
            std::memcpy(&hash, state.field.data(), sizeof(hash));
            return hash;
        }
    };

    Puzzle(Puzzle const &other)
    : field(other.field),
    emptyPos(other.emptyPos) {
    }

    bool operator==(const Puzzle &other) const
    {
        return this->field == other.field;
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
                        + 10 * abs(i % FIELD_SIZE - (futureField[i] - 1) % FIELD_SIZE); // перемещение по горизонтали
                h += moving; // добавляем в эвристику число ходов для постановкии костяшки на место
            }
        }
        return h;
    }

    std::string SolveAStar(std::array<int, FIELD_SIZE> field) {
        Puzzle startState(field);

        std::map<int, Puzzle> priority_queue;
        priority_queue.insert(std::pair<int, Puzzle>(0 + heuristic(startState), startState));

        std::unordered_map<Puzzle, char, MyHash> visited;
        visited[startState] = 'S';

        while (true) { // построение графа решений
            Puzzle curState = (priority_queue.begin())->second;
            int depth = (priority_queue.begin())->first;
            priority_queue.erase(priority_queue.begin());

            if (curState.IsComplete())
                break;

            if (curState.CanMoveLeft()) {
                Puzzle newState = curState.MoveLeft();
                if (visited.find(newState) == visited.end()) { // если такого состояния еще не было
                    priority_queue.insert(std::pair<int, Puzzle>(depth + 1 + heuristic(newState), newState));
                    visited[newState] = 'L';
                }
            }

            if (curState.CanMoveRight()) {
                Puzzle newState = curState.MoveRight();
                if (visited.find(newState) == visited.end()) { // если такого состояния еще не было
                    priority_queue.insert(std::pair<int, Puzzle>(depth + 1 + heuristic(newState), newState));
                    visited[newState] = 'R';
                }
            }

            if (curState.CanMoveUp()) {
                Puzzle newState = curState.MoveUp();
                if (visited.find(newState) == visited.end()) { // если такого состояния еще не было
                    priority_queue.insert(std::pair<int, Puzzle>(depth + 1 + heuristic(newState), newState));
                    visited[newState] = 'U';
                }
            }

            if (curState.CanMoveDown()) {
                Puzzle newState = curState.MoveDown();
                if (visited.find(newState) == visited.end()) { // если такого состояния еще не было
                    priority_queue.insert(std::pair<int, Puzzle>(depth + 1 + heuristic(newState), newState));
                    visited[newState] = 'D';
                }
            }
        }

        std::string path; // поиск пути
        Puzzle state(finalField);
        while (visited[state] != 'S') {
            char move = visited[state];
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

    std::array<int, FIELD_SIZE> field;
private:
    //std::array<int, FIELD_SIZE> field;
    int emptyPos;
};




int main() {
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