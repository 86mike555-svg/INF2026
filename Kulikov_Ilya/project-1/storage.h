#ifndef STORAGE_h
#define STORAGE_h

template <class T, unsigned int S> class Storage {
    T *buf[S];
    bool is_full;
    Storage *next;

  public:
    Storage() : is_full(false), next(0) {
        for (unsigned int index = 0; index < S; ++index)
            buf[index] = 0;
    }

    void append(T *value) {
        if (is_full) {
            if (next == 0)
                next = new Storage;
            next->append(value);
        }

        unsigned int index = 0;
        for (; index < S; ++index) {
            if (buf[index] == 0) {
                buf[index] = value;
                break;
            }
        }

        if (index == S - 1)
            is_full = true;
    }

    void remove(bool predicate(const T &)) {
        for (unsigned int index = 0; index < S; ++index)
            if (buf[index] != 0 && predicate(*buf[index])) {
                delete buf[index];
                buf[index] = 0;
                is_full = false;
            }

        if (next != 0)
            next->remove(predicate);
    }

    // Reference should not be used, if `valid` equals `false`.
    T &select_first(bool predicate(const T &), bool &valid) {
        for (unsigned int index = 0; index < S; ++index) {
            if (buf[index] != 0 && predicate(*buf[index])) {
                valid = true;
                return (buf[index]);
            }
        }

        if (next != 0)
            return next->select_first(predicate);
        else
            valid = false;
    }

    void foreach (void procedure(const T &)) {
        for (unsigned int index = 0; index < S; ++index)
            if (buf[index] != 0)
                procedure(*buf[index]);

        if (next != 0) {
            next->foreach (procedure);
        }
    }

    ~Storage() {
        for (unsigned int index = 0; index < S; ++index)
            if (buf[index] != 0)
                delete buf[index];

        if (next != 0) {
            delete next;
            next = 0;
        }
    }
};

#endif
