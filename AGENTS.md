# AGENTS.md - AI 助手指南

本文件为 AI 编码助手（如 Cursor）提供项目上下文和开发指南。

## 项目概述

本项目是 **《Algorithm Design》算法设计** 的代码笔记仓库，包含经典算法和数据结构的实现，主要用于学习和参考。

## 目录结构

```
workspace/
├── divide_and_conquer/     # 分治算法
│   ├── merge_sort.cpp      # 归并排序
│   ├── quick_sort.cpp      # 快速排序
│   └── quick_select.cpp    # 快速选择
├── data_structure/         # 数据结构
│   ├── binary_indexed_tree.cpp  # 树状数组
│   ├── segment_tree.cpp    # 线段树
│   ├── heap_sort.cpp       # 堆排序 (C++)
│   └── heap_sort.py        # 堆排序 (Python)
├── greedy/                 # 贪心算法
│   ├── dijkstra.cpp        # Dijkstra 最短路
│   ├── prim.cpp            # Prim 最小生成树
│   └── kruskal.cpp         # Kruskal 最小生成树
├── dynamic_programming/    # 动态规划
│   ├── bellman_ford.cpp    # Bellman-Ford 最短路
│   ├── floyd.cpp           # Floyd 最短路
│   └── knapsack.cpp        # 背包问题
├── network_flow/           # 网络流
│   └── dinic.cpp           # Dinic 最大流
├── README.md
└── AGENTS.md
```

## 技术栈

- **主要语言**: C++（算法实现）
- **辅助语言**: Python（部分实现）
- **代码格式化**: `.clang-format`（IndentWidth: 4）

## 编码规范

### C++ 代码

1. **缩进**: 使用 4 空格缩进（遵循 `.clang-format`）
2. **注释风格**: 算法文件头部应包含：
   - 算法名称（中文）
   - 时间复杂度
   - 稳定性（如适用）
3. **命名**: 使用 `snake_case` 或 `my_` 前缀区分自定义实现
4. **标准库**: 使用 `std::vector`、`std::iostream` 等 STL 容器

### Python 代码

1. **风格**: 遵循 PEP 8
2. **简洁性**: 算法实现保持简洁，可适当使用标准库（如 `heapq`）

## 开发指南

### 添加新算法时

1. 将文件放入对应的算法分类目录
2. 在文件头部添加算法说明注释（名称、复杂度等）
3. 包含可运行的 `main()` 或测试用例
4. 使用与现有代码一致的风格

### 修改现有代码时

1. 保持算法正确性优先
2. 不改变已有的代码风格和注释语言（中英混合）
3. 运行前确保代码可编译/执行

## 常见任务

- **添加新算法**: 在相应目录创建 `.cpp` 或 `.py` 文件
- **优化实现**: 保持接口和测试用例不变，优化内部实现
- **修复 Bug**: 优先保证算法正确性，注意边界情况
- **添加注释**: 使用中文描述算法逻辑，英文用于代码内注释

## 注意事项

- 本项目为学习用途，代码以清晰易懂为主
- 各算法文件应独立可运行，包含必要的 `#include` 和 `main` 函数
- 测试数据通常使用简单示例（如 `{9, 0, 8, 1, 7, 2, 6, 3, 5, 4}`）
