# 算法设计与分析实验课程仓库

本仓库按照《算法设计与分析实验指导书》的要求，完成了四个实验项目：

1. 实验一 `查找假币问题`：分治法
2. 实验二 `迷宫路径`：回溯法
3. 实验三 `在原始森林中解救A`：分支限界法
4. 实验四 `赶作业`：贪心法

## 仓库结构

- `exp1_fake_coin/`：实验一代码、样例、说明
- `exp2_maze_paths/`：实验二代码、样例、说明
- `exp3_rescue_a/`：实验三代码、样例、说明
- `exp4_homework_scheduling/`：实验四代码、样例、说明
- `reports/`：四份实验报告 `.docx`
- `scripts/generate_reports.py`：根据模板生成四份实验报告

## 构建方式

```bash
cmake -S . -B build
cmake --build build
```

## 运行示例

```bash
./build/exp1_fake_coin < exp1_fake_coin/samples/sample_input.txt
./build/exp2_maze_paths < exp2_maze_paths/samples/sample_input.txt
./build/exp3_rescue_a < exp3_rescue_a/samples/sample_input.txt
./build/exp4_homework_scheduling < exp4_homework_scheduling/samples/sample_input.txt
```

## 报告与截图

四份实验报告已在 `reports/` 目录生成，内容包含：

- 实验题目与要求
- 算法策略说明
- 算法框架回答
- 时间复杂度或关键分析
- 测试说明与结果分析
- 截图占位说明

另附 `reports/截图清单.md`，分实验列出了完成最终提交时建议补充的截图。

