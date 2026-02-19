#ifndef FLAG_FIELD_h
#define FLAG_FIELD_h

#include <cstdio>
class FlagField {
    using Integer = unsigned int;

    // little bits correspond with smaller indexes
    Integer flags;

  public:
    FlagField() : flags(0) {}

    static const Integer length = 8 * sizeof(int);

    using Bit = bool;

    inline bool all_up() { return ~flags == 0; }
    inline bool all_down() { return flags == 0; };
    inline bool some_up() { return flags != 0; }
    inline bool some_down() { return ~flags != 0; }

    // returns `-1` if there is no up flags.
    Integer get_first_up_index() {
        for (Integer index = 0; index < length; ++index) {
            if ((flags & (1 << index)) != 0)
                return index;
        }

        return -1;
    }

    // returns `-1` if there is no down flags.
    Integer get_first_down_index() {
        for (Integer index = 0; index < length; ++index) {
            if ((~flags & (1 << index)) != 0)
                return index;
        }

        return -1;
    }

    // Contract: `index` should be in [0; `length`).
    // UB otherwise.
    inline Bit get_ith_flag(Integer index) {
        Integer masked = flags & (1 << index);
        if (masked != 0)
            return true;
        else
            return false;
    }

    // Contract: `index` should be in [0; `length`).
    // UB otherwise.
    inline void set_ith_flag(Integer index, Bit state) {
        if (state)
            flags |= (1 << index);
        else
            flags = ~((~flags) | (1 << index));
    }

    void print() { printf("%0*b\n", length, flags); }
};

#endif
