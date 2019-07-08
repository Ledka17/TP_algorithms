#include <array>
#include <map>
#include <iostream>
#include <stdlib.h>
#include <unordered_map>
#include <algorithm>

const int SIDE_SIZE = 4;
const int FIELD_SIZE = 16;
const std::array<int, FIELD_SIZE> finalField = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};


class Puzzle {
public:
    Puzzle() : field() {}
    Puzzle(std::array<int, FIELD_SIZE> field);
    Puzzle(Puzzle const &other);

    bool IsComplete();
    bool CanMoveLeft();
    bool CanMoveRight();
    bool CanMoveUp();
    bool CanMoveDown();

    Puzzle MoveLeft();
    Puzzle MoveRight();
    Puzzle MoveUp();
    Puzzle MoveDown();

    bool IsSolvable();
    int heuristic(Puzzle futurePuzzle);
    int transform(std::array<int, FIELD_SIZE> field);
    std::string SolveAStar(std::array<int, FIELD_SIZE> field);

    friend std::ostream& operator<<(std::ostream &out, const Puzzle &state);
    friend bool operator<(const Puzzle &L, const Puzzle &R) { return true; };

    std::array<int, FIELD_SIZE> field;
    int emptyPos;
};

typedef std::pair<int, Puzzle> q_t;

class priority_queue {
public:
    priority_queue();
    ~priority_queue();

    q_t pop();
    void emplace(q_t val);

private:
    void siftUp(int index);
    void siftDown(int index);

    q_t *buffer_;
    int defaultSize_;
    int bufferSize_;
    int size_;
};


Puzzle::Puzzle(std::array<int, FIELD_SIZE> field)
    : field(field) {
        emptyPos = -1;
        for (int i = 0; i < FIELD_SIZE; i++) {
            if (field[i] == 0)
                emptyPos = i;
        }
}

Puzzle::Puzzle(Puzzle const &other)
    : field(other.field),
    emptyPos(other.emptyPos) {
}

bool Puzzle::IsComplete() {
    return field == finalField;
}

bool Puzzle::CanMoveLeft() {
    return emptyPos % SIDE_SIZE != SIDE_SIZE - 1;
}

bool Puzzle::CanMoveRight() {
    return emptyPos % SIDE_SIZE != 0;
}

bool Puzzle::CanMoveUp() {
    return emptyPos % SIDE_SIZE < FIELD_SIZE - SIDE_SIZE;
}

bool Puzzle::CanMoveDown() {
    return emptyPos % SIDE_SIZE > SIDE_SIZE - 1;
}

Puzzle Puzzle::MoveLeft() {
    Puzzle newPuzzle(*this);
    std::swap(newPuzzle.field[emptyPos], newPuzzle.field[emptyPos + 1]);
    newPuzzle.emptyPos++;
    return newPuzzle;
}

Puzzle Puzzle::MoveRight() {
    Puzzle newPuzzle(*this);
    std::swap(newPuzzle.field[emptyPos], newPuzzle.field[emptyPos - 1]);
    newPuzzle.emptyPos--;
    return newPuzzle;
}

Puzzle Puzzle::MoveUp() {
    Puzzle newPuzzle(*this);
    std::swap(newPuzzle.field[emptyPos], newPuzzle.field[emptyPos + SIDE_SIZE]);
    newPuzzle.emptyPos += SIDE_SIZE;
    return newPuzzle;
}

Puzzle Puzzle::MoveDown() {
    Puzzle newPuzzle(*this);
    std::swap(newPuzzle.field[emptyPos], newPuzzle.field[emptyPos - SIDE_SIZE]);
    newPuzzle.emptyPos -= SIDE_SIZE;
    return newPuzzle;
}

bool Puzzle::IsSolvable() {
    int inversions = 0;
    for (int i = 0; i < FIELD_SIZE; i++)
        for (int j = i + 1; j < FIELD_SIZE; j++)
            if (field[i] != 0 && field[j] != 0 && field[i] > field[j])
                inversions++;
            return (inversions % 2 == 0) == (emptyPos / 4 % 2 == 1);
}

int Puzzle::heuristic(Puzzle futurePuzzle) {
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

int Puzzle::transform(std::array<int, FIELD_SIZE> field) {
    int t = 0;
    for (int i = 0; i < FIELD_SIZE; i++) {
        t += (i + 1) * field[i];
    }
    return t;
}

std::string Puzzle::SolveAStar(std::array<int, FIELD_SIZE> field) {
    Puzzle startState(field);

    priority_queue q;
    q.emplace(std::pair<int, Puzzle>(0, startState));

    std::unordered_map<int, char> visited;
    visited[transform(startState.field)] = 'S';

    while (true) { // построение графа решений
        q_t cur = q.pop();
        Puzzle curState = cur.second;
        //int depth = cur.first - heuristic(curState);

        if (curState.IsComplete())
            break;

        if (curState.CanMoveLeft()) {
            // std::cout << "Left" << std::endl;
            Puzzle newState = curState.MoveLeft();
            if (visited.find(transform(newState.field)) == visited.end()) { // если такого состояния еще не было
                q.emplace(std::pair<int, Puzzle>( heuristic(newState), newState));
                visited[transform(newState.field)] = 'L';
            }
            //std::cout << newState << std::endl;
        }

        if (curState.CanMoveRight()) {
            //std::cout << "Right" << std::endl;
            Puzzle newState = curState.MoveRight();
            if (visited.find(transform(newState.field)) == visited.end()) { // если такого состояния еще не было
                q.emplace(std::pair<int, Puzzle>( heuristic(newState), newState));
                visited[transform(newState.field)] = 'R';
            }
            //std::cout << newState << std::endl;
        }

        if (curState.CanMoveUp()) {
            //std::cout << "Up" << std::endl;
            Puzzle newState = curState.MoveUp();
            if (visited.find(transform(newState.field)) == visited.end()) { // если такого состояния еще не было
                q.emplace(std::make_pair( heuristic(newState), newState));
                visited[transform(newState.field)] = 'U';
            }
            //std::cout << newState << std::endl;
        }

        if (curState.CanMoveDown()) {
            //std::cout << "Down" << std::endl;
            Puzzle newState = curState.MoveDown();
            if (visited.find(transform(newState.field)) == visited.end()) { // если такого состояния еще не было
                q.emplace(std::pair<int, Puzzle>( heuristic(newState), newState));
                visited[transform(newState.field)] = 'D';
            }
            //std::cout << newState << std::endl;
        }
        //std::cout << curState << std::endl;
    }

    std::string path; // поиск пути
    Puzzle state(finalField);
    while (visited[transform(state.field)] != 'S') {
        char move = visited[transform(state.field)];
        path += move;
        switch (move) {
                case 'L':
                    state = state.MoveRight();
                    break;
                case 'R':
                    state = state.MoveLeft();
                    break;
                case 'U':
                    state = state.MoveDown();
                    break;
                case 'D':
                    state = state.MoveUp();
                    break;
        }
    }

    std::reverse(path.begin(), path.end());
    return path;
}

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



priority_queue::priority_queue() :
        defaultSize_(16),
        bufferSize_(defaultSize_),
        size_(0) {
    buffer_ = new q_t[bufferSize_];
}


priority_queue::~priority_queue() {
    delete[] buffer_;
}


void priority_queue::emplace(q_t val) {
    if (size_ + 1 > bufferSize_) {
        q_t *tmp = new q_t[bufferSize_ * 2];
        for (int i = 0; i < bufferSize_; i++)
            tmp[i] = buffer_[i];
        delete[] buffer_;
        buffer_ = tmp;
        bufferSize_ *= 2;
    }
    buffer_[size_] = val;
    size_++;
    siftUp(size_ - 1);
}


q_t priority_queue::pop() {
    q_t max = buffer_[0];
    buffer_[0] = buffer_[size_ - 1];
    size_--;
    if (size_)
        siftDown(0);
    return max;
}


void priority_queue::siftUp(int index) {
    while (index && buffer_[index] < buffer_[(index - 1) / 2]) {
        q_t tmp = buffer_[index];
        buffer_[index] = buffer_[(index - 1) / 2];
        buffer_[(index - 1) / 2] = tmp;
        index = (index - 1) / 2;
    }
}


void priority_queue::siftDown(int index) {
    int max = index;
    if (index * 2 + 1 < size_
        && buffer_[index * 2 + 1] < buffer_[max])
        max = index * 2 + 1;
    if (index * 2 + 2 < size_
        && buffer_[index * 2 + 2] < buffer_[max])
        max = index * 2 + 2;
    if (max != index) {
        q_t tmp = buffer_[index];
        buffer_[index] = buffer_[max];
        buffer_[max] = tmp;
        siftDown(max);
    }
}