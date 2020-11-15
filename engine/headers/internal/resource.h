#pragma once

namespace sfx {
    void clean();
    void init();
}

namespace spr {
    void update();
    void clean();
    void push();
    void init();
    void flush();
}

namespace res {
    void init();
    void close();
}
