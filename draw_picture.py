import matplotlib.pyplot as plt

file_path = "D:/卫星导航算法课程/result.txt"

# 读取文件内容
with open(file_path, "r") as file:
    lines = file.readlines()

# 解析数据
E = []
N = []
U = []
Vx = []
Vy = []
Vz = []
PDOP = []

for line in lines[1:]:
    values = line.strip().split()
    try:
        e = float(values[0])
        n = float(values[1])
        u = float(values[2])
        vx = float(values[3])
        vy = float(values[4])
        vz = float(values[5])
        pdop = float(values[6])
        E.append(e)
        N.append(n)
        U.append(u)
        Vx.append(vx)
        Vy.append(vy)
        Vz.append(vz)
        PDOP.append(pdop)
    except ValueError:
        # 在转换失败时忽略该行数据
        continue

# 计算每个方向的RMS
rms_E = (sum([x**2 for x in E])/len(E))**0.5
rms_N = (sum([x**2 for x in N])/len(N))**0.5
rms_U = (sum([x**2 for x in U])/len(U))**0.5
rms_Vx = (sum([x**2 for x in Vx])/len(Vx))**0.5
rms_Vy = (sum([x**2 for x in Vy])/len(Vy))**0.5
rms_Vz = (sum([x**2 for x in Vz])/len(Vz))**0.5
rms_PDOP = (sum([x**2 for x in PDOP])/len(PDOP))**0.5

# 打印计算结果
print("E坐标的RMS误差：", rms_E)
print("N坐标的RMS误差：", rms_N)
print("U坐标的RMS误差：", rms_U)
print("Vx坐标的RMS误差：", rms_Vx)
print("Vy坐标的RMS误差：", rms_Vy)
print("Vz坐标的RMS误差：", rms_Vz)
print("PDOP值的RMS误差：", rms_PDOP)

# 绘制时序图
# 创建第一个画布，包含E、N、U的时序图
fig1, (ax1, ax2, ax3) = plt.subplots(3, 1, figsize=(8, 15))
ax1.plot(E)
ax1.set_ylabel("E/m")
ax2.plot(N)
ax2.set_ylabel("N/m")
ax3.plot(U)
ax3.set_ylabel("U/m")
plt.xlabel("t/s")
plt.suptitle("E, N, U")

# 创建第二个画布，包含Vx、Vy、Vz的时序图
fig2, (ax4, ax5, ax6) = plt.subplots(3, 1, figsize=(8, 15))
ax4.plot(Vx)
ax4.set_ylabel("Vx(m/s)")
ax5.plot(Vy)
ax5.set_ylabel("Vy(m/s)")
ax6.plot(Vz)
ax6.set_ylabel("Vz(m/s)")
plt.xlabel("t(s)")
plt.suptitle("Vx, Vy, Vz")

# 创建第三个画布，包含PDOP的时序图
plt.figure(figsize=(8, 6))
plt.plot(PDOP)
plt.ylabel("PDOP")
plt.xlabel("t(s)")
plt.title("PDOP")

# 显示图形
plt.show()