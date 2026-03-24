import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
from matplotlib.ticker import AutoMinorLocator
from mpl_toolkits.axes_grid1.inset_locator import inset_axes, mark_inset
from scipy import stats

mpl.rcParams.update({
    "font.family":         "serif",
    "font.serif":          ["Times New Roman"],
    "font.size":           10,
    "axes.labelsize":      10,
    "legend.fontsize":     8,
    "xtick.direction":     "in",
    "ytick.direction":     "in",
    "xtick.top":           True,
    "ytick.right":         True,
    "xtick.major.size":    4,
    "ytick.major.size":    4,
    "xtick.minor.size":    2,
    "ytick.minor.size":    2,
    "xtick.minor.visible": True,
    "ytick.minor.visible": True,
    "axes.linewidth":      0.8,
})

VISUAL_STYLES = {
    "rho_exact": ("#000000", "-",           1.0, "Exact"),
    "rho_muscl": ("#ff7f0e", (0,(3,1)),     0.8, "MUSCL"),
    "rho_ader3": ("#2ca02c", (0,(1,1)),     0.8, "ADER3"),
    "rho_ader4": ("#9467bd", (0,(6,1,1,1)), 0.8, "ADER4"),
    "rho_ader5": ("#d62728", "-",           1.0, "ADER5"),
}

EFF_STYLES = {
    "MUSCL": ("#ff7f0e", "o", (0,(3,1))),
    "ADER3": ("#2ca02c", "s", (0,(1,1))),
    "ADER4": ("#9467bd", "^", (0,(6,1,1,1))),
    "ADER5": ("#d62728", "D", "-"),
}

# --- Convergence profile plot (task_3_4_convergence.csv) ---
df = pd.read_csv("task_3_4_convergence.csv")

fig, ax = plt.subplots(figsize=(6.7, 3.2))
for col, (color, ls, lw, label) in VISUAL_STYLES.items():
    ax.plot(df["x"], df[col], color=color, linestyle=ls, linewidth=lw, label=label)
ax.set_xlabel(r"$x$")
ax.set_ylabel(r"$\rho$")
ax.set_xlim(-1, 1)
ax.legend(frameon=False, ncol=5, loc="upper right")
ax.xaxis.set_minor_locator(AutoMinorLocator(4))
ax.yaxis.set_minor_locator(AutoMinorLocator(4))

axins = inset_axes(ax, width="28%", height="32%", loc="upper center",
                   bbox_to_anchor=(0.0, -0.15, 1, 1),
                   bbox_transform=ax.transAxes)
for col, (color, ls, lw, label) in VISUAL_STYLES.items():
    axins.plot(df["x"], df[col], color=color, linestyle=ls, linewidth=lw)
axins.set_xlim(0.38, 0.62)
axins.set_ylim(2.88, 3.02)
axins.tick_params(labelsize=7)
axins.xaxis.set_minor_locator(AutoMinorLocator(2))
axins.yaxis.set_minor_locator(AutoMinorLocator(2))
mark_inset(ax, axins, loc1=3, loc2=4, fc="none", ec="0.5", lw=0.6)

fig.tight_layout()
fig.savefig("task_3_4_convergence.png", dpi=300)
plt.show()
print("saved task_3_4_convergence.png")

# --- Efficiency plot (task_3_4_efficiency.csv) ---
# NOTE: the C++ solver writes task_3_4_efficiency.csv.
# If you run multiple experiments at different T values, rename the output
# files manually (e.g. task_3_4_efficiency_T400.csv) before plotting.
eff_csv = "task_3_4_efficiency.csv"
df2 = pd.read_csv(eff_csv)

fig, ax = plt.subplots(figsize=(6.7, 4.0))

for scheme, (color, marker, ls) in EFF_STYLES.items():
    sub = df2[df2["scheme"] == scheme].sort_values("cpu_sec")
    if sub.empty:
        continue
    x = np.log10(sub["cpu_sec"].values)
    y = np.log10(sub["L2"].values)
    slope, intercept, _, _, _ = stats.linregress(x, y)

    ax.plot(sub["cpu_sec"], sub["L2"], color=color, linestyle="--",
            linewidth=0.5, alpha=0.4, zorder=2)
    ax.plot(sub["cpu_sec"], sub["L2"], color=color, linestyle="none",
            marker=marker, markersize=5, zorder=4)

    x_fit = np.linspace(x.min(), x.max(), 50)
    y_fit = slope * x_fit + intercept
    ax.plot(10**x_fit, 10**y_fit, color=color, linestyle="-",
            linewidth=1.2, label=f"{scheme} (slope={slope:.2f})", zorder=3)

ax.set_xscale("log")
ax.set_yscale("log")
ax.set_xlabel("CPU time (s)")
ax.set_ylabel(r"$L_2$ error")
ax.axhline(y=1e-3, color="gray", linestyle="--", linewidth=0.8,
           label=r"$L_2 = 10^{-3}$")
ax.legend(frameon=False)
fig.tight_layout()
fig.savefig("task_3_4_efficiency.png", dpi=300)
plt.show()
print("saved task_3_4_efficiency.png")