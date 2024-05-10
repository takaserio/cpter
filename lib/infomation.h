#define PORT 3000;

struct Cpu {
    char cpu_name[256];
    //unsigned int cpu_temperture;
};

struct Memory {
    //unsigned int mem_total;
    //unsigned int mem_usage;

    char mem_total[256];
    char mem_usage[256];
};

struct Info {
    struct Cpu cpu;
    struct Memory memory;
};