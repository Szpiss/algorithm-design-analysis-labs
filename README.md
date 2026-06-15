# 算法设计与分析实验课程仓库

本仓库统一整理《算法设计与分析》课程实验代码、样例输入和 Word 实验报告。四个实验按算法策略拆分目录，根目录提供统一构建方式，避免每个实验单独建仓库造成重复。

## 实验清单

| 实验 | 目录 | 算法策略 | 主要目标 |
| --- | --- | --- | --- |
| 实验一：查找假币问题 | `exp1_fake_coin/` | 分治法 | 在一组硬币中通过称重策略定位假币 |
| 实验二：迷宫路径 | `exp2_maze_paths/` | 回溯法 | 搜索迷宫中的可行路径并输出过程 |
| 实验三：在原始森林中解救 A | `exp3_rescue_a/` | 分支限界法 | 在约束条件下寻找救援最优路径 |
| 实验四：赶作业 | `exp4_homework_scheduling/` | 贪心法 | 根据截止时间和收益安排作业顺序 |

## 仓库结构

```text
algorithm-design-analysis-labs/
├── CMakeLists.txt
├── exp1_fake_coin/
│   ├── src/
│   ├── samples/
│   └── README.md
├── exp2_maze_paths/
├── exp3_rescue_a/
├── exp4_homework_scheduling/
├── reports/                         # 四份实验报告和截图清单
└── scripts/generate_reports.py       # 报告生成辅助脚本
```

## 构建与运行

统一使用 CMake 构建：

```bash
cmake -S . -B build
cmake --build build
```

运行示例：

```bash
./build/exp1_fake_coin < exp1_fake_coin/samples/sample_input.txt
./build/exp2_maze_paths < exp2_maze_paths/samples/sample_input.txt
./build/exp3_rescue_a < exp3_rescue_a/samples/sample_input.txt
./build/exp4_homework_scheduling < exp4_homework_scheduling/samples/sample_input.txt
```

## 报告材料

`reports/` 目录保存四份实验报告，内容包含：

- 实验题目与问题分析
- 算法设计思路和核心流程
- 关键代码或伪代码说明
- 时间复杂度/策略分析
- 测试数据、运行结果和结论

截图补充建议见：

```text
reports/截图清单.md
```

## 维护规则

- 同一门算法课程的新实验继续放入本仓库，不再拆成新的重复仓库。
- 每个实验目录保留独立 README，根 README 负责总览和统一构建说明。
- 报告、样例、源码同步提交，保证 GitHub 页面可以直接浏览提交内容。
