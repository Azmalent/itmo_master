// pch.h: это предварительно скомпилированный заголовочный файл.
// Перечисленные ниже файлы компилируются только один раз, что ускоряет последующие сборки.
// Это также влияет на работу IntelliSense, включая многие функции просмотра и завершения кода.
// Однако изменение любого из приведенных здесь файлов между операциями сборки приведет к повторной компиляции всех(!) этих файлов.
// Не добавляйте сюда файлы, которые планируете часто изменять, так как в этом случае выигрыша в производительности не будет.

#ifndef PCH_H
#define PCH_H

// Добавьте сюда заголовочные файлы для предварительной компиляции
#include "include/components/component.h"
#include "include/components/fpsCounter.h"
#include "include/components/mesh.h"
#include "include/delegates.h"
#include "include/game.h"
#include "include/input.h"
#include "include/keys.h"
#include "include/mesh.h"
#include "include/render.h"
#include "include/shader.h"
#include "include/window.h"

#endif //PCH_H
