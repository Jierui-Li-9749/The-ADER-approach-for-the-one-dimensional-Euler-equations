import pandas as pd
import matplotlib.pyplot as plt
import matplotlib as mpl
from mpl_toolkits.axes_grid1.inset_locator import inset_axes, mark_inset
from matplotlib.ticker import AutoMinorLocator

mpl.rcParams.update({
    "font.family":         "serif",
    "font.serif":          ["Times New Roman"],
    "font.size":           10,
    "axes.labelsize":      12,
    "legend.fontsize":     9,
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

# (column, color, linestyle, linewidth, label, zorder)
SCHEMES = [
    ("rho_muscl", "#ff7f0e", "--",  1.8, "MUSCL",  3),
    ("rho_ader3", "#2ca02c", "-.",  1.0, "ADER3",  4),
    ("rho_ader4", "#1f77b4", ":",   1.2, "ADER4",  4),
    ("rho_ader5", "#d62728", "-",   0.9, "ADER5",  5),
]

df = pd.read_csv("task_3_3.csv")
mask = (df["x"] >= -2.5) & (df["x"] <= 3.5)
df = df[mask].reset_index(drop=True)

fig, ax = plt.subplots(figsize=(7.5, 4.0))

ax.plot(df["x"], df["rho_ref"], color="black", linestyle="-",
        linewidth=0.7, label=r"Reference (ADER5, $N=4000$)", zorder=6)

for col, color, ls, lw, label, zo in SCHEMES:
    ax.plot(df["x"], df[col], color=color, linestyle=ls,
            linewidth=lw, label=label, zorder=zo)

ax.set_xlabel(r"$x$")
ax.set_ylabel(r"$\rho$")
ax.set_xlim(-2.5, 3.5)
ax.legend(frameon=True, fancybox=False, edgecolor="0.7",
          ncol=3, loc="upper right", fontsize=8)
ax.xaxis.set_minor_locator(AutoMinorLocator(4))
ax.yaxis.set_minor_locator(AutoMinorLocator(4))

# Zoom inset on the high-frequency region
axins = inset_axes(ax, width="42%", height="48%", loc="lower left",
                   bbox_to_anchor=(0.04, 0.04, 1, 1),
                   bbox_transform=ax.transAxes)

zoom_lo, zoom_hi = -1.0, 0.0
mask2 = (df["x"] >= zoom_lo) & (df["x"] <= zoom_hi)
df2 = df[mask2]

axins.plot(df2["x"], df2["rho_ref"], color="black", linestyle="-",
           linewidth=0.7, zorder=6)
for col, color, ls, lw, label, zo in SCHEMES:
    axins.plot(df2["x"], df2[col], color=color, linestyle=ls,
               linewidth=lw, zorder=zo)

axins.set_xlim(zoom_lo, zoom_hi)
axins.tick_params(labelsize=7, direction="in")
axins.xaxis.set_minor_locator(AutoMinorLocator(4))
axins.yaxis.set_minor_locator(AutoMinorLocator(4))

mark_inset(ax, axins, loc1=2, loc2=4, fc="none", ec="0.5", lw=0.6)

fig.tight_layout()
fig.savefig("task_3_3.png", dpi=300, bbox_inches="tight")
plt.show()
print("saved task_3_3.png")