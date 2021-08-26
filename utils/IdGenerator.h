#pragma once

class IdGenerator {
public:
    size_t generate_id() {
        return count++;
    }
private:
    size_t count = 0;
};
