import pandas as pd
import matplotlib.pyplot as plt
import matplotlib as mpl
import matplotlib.ticker as ticker
from mpl_toolkits.axes_grid1.inset_locator import mark_inset

mpl.rcParams.update({
    "font.family":       "serif",
    "font.serif":        ["Times New Roman", "DejaVu Serif"],
    "mathtext.fontset":  "stix",
    "font.size":         10,
    "axes.labelsize":    10,
    "axes.titlesize":    10,
    "legend.fontsize":   8,
    "xtick.labelsize":   9,
    "ytick.labelsize":   9,
    "xtick.direction":   "in",
    "ytick.direction":   "in",
    "xtick.major.size":  4.0,
    "ytick.major.size":  4.0,
    "xtick.minor.size":  2.0,
    "ytick.minor.size":  2.0,
    "xtick.major.width": 0.8,
    "ytick.major.width": 0.8,
    "xtick.top":         True,
    "ytick.right":       True,
    "axes.linewidth":    0.6,
    "lines.linewidth":   0.6,
    "legend.framealpha": 0.9,
    "legend.edgecolor":  "0.5",
    "legend.handlelength": 3.0,
})

# (column_key, color, linestyle, linewidth, label)
SCHEMES = [
    ("exact", "#000000", "-",                   1.2, "Exact"),
    ("god1",  "#1f77b4", (0,(6,2)),             0.8, "Godunov"),
    ("muscl", "#ff7f0e", (0,(3,1)),             0.8, "MUSCL"),
    ("ader3", "#2ca02c", (0,(1,1)),             0.8, "ADER3"),
    ("ader4", "#9467bd", (0,(6,1,1,1)),         0.8, "ADER4"),
    ("ader5", "#d62728", (0,(3,1,1,1,1,1)),     0.8, "ADER5"),
]

sod = pd.read_csv("task_3_2_sod.csv")
lax = pd.read_csv("task_3_2_lax.csv")


def plot_lines(ax, df, var):
    for key, color, ls, lw, label in SCHEMES:
        col = f"{var}_{key}"
        if col in df.columns:
            ax.plot(df["x"], df[col], color=color, linestyle=ls,
                    linewidth=lw, label=label)
    ax.set_xlim(0.0, 1.0)
    ax.set_xlabel(r"$x$")
    ax.xaxis.set_major_locator(ticker.MultipleLocator(0.2))
    ax.xaxis.set_minor_locator(ticker.AutoMinorLocator(4))
    ax.yaxis.set_minor_locator(ticker.AutoMinorLocator(4))
    ax.grid(False)


def add_zoom(ax, df, var, x1, x2, y1, y2, loc):
    axins = ax.inset_axes(loc)
    for key, color, ls, lw, _ in SCHEMES:
        col = f"{var}_{key}"
        if col in df.columns:
            axins.plot(df["x"], df[col], color=color, linestyle=ls, linewidth=lw)
    axins.set_xlim(x1, x2)
    axins.set_ylim(y1, y2)
    axins.tick_params(labelsize=5.5)
    axins.xaxis.set_minor_locator(ticker.AutoMinorLocator(2))
    axins.yaxis.set_minor_locator(ticker.AutoMinorLocator(2))
    mark_inset(ax, axins, loc1=2, loc2=4, fc="none", ec="0.5", lw=0.6)


# Zoom regions: (x1, x2, y1, y2, inset_bbox)
ZOOM = {
    "rho": {
        "sod": (0.60, 0.76, 0.25, 0.44, [0.55, 0.50, 0.20, 0.25]),
        "lax": (0.76, 0.96, 0.42, 0.60, [0.05, 0.50, 0.20, 0.25]),  # fixed: Lax post-shock density ~0.4-0.6
    },
    "u": {
        "sod": (0.44, 0.56, 0.91, 1.01, [0.55, 0.10, 0.20, 0.25]),
        "lax": (0.35, 0.45, 1.50, 1.62, [0.05, 0.50, 0.20, 0.25]),
    },
    "p": {
        "sod": (0.80, 0.92, 0.27, 0.34, [0.55, 0.50, 0.20, 0.25]),
        "lax": (0.88, 0.99, 2.38, 2.56, [0.05, 0.50, 0.20, 0.25]),
    },
}

VARS = [("rho", r"$\rho$"), ("u", r"$u$"), ("p", r"$p$")]

# Three-panel figures (one per test case)
for df, title, sub, out in [
    (sod, "Sod Shock Tube", "N=355, T=0.2, CFL=0.9",  "task_3_2_sod.png"),
    (lax, "Lax Problem",    "N=355, T=0.14, CFL=0.9", "task_3_2_lax.png"),
]:
    fig, axes = plt.subplots(1, 3, figsize=(13, 3.8))
    for i, (ax, (var, ylabel)) in enumerate(zip(axes, VARS)):
        plot_lines(ax, df, var)
        ax.set_ylabel(ylabel)
        ax.set_title(f"({'abc'[i]}) {ylabel}", fontsize=9, loc="left")
        if i == 0:
            ax.legend(loc="lower left", fontsize=7)
    plt.tight_layout()
    plt.savefig(out, dpi=300, bbox_inches="tight")
    print(f"Saved {out}")
    plt.show()

# Per-variable figures with zoom insets
VAR_OUT = {
    "rho": "task_3_2_density.png",
    "u":   "task_3_2_velocity.png",
    "p":   "task_3_2_pressure.png",
}

for var, ylabel in VARS:
    fig, axes = plt.subplots(1, 2, figsize=(9, 3.8))
    for i, (ax, df, ckey, cname) in enumerate([
        (axes[0], sod, "sod", "Sod Shock Tube"),
        (axes[1], lax, "lax", "Lax Problem"),
    ]):
        plot_lines(ax, df, var)
        ax.set_ylabel(ylabel)
        ax.set_title(f"({'ab'[i]}) {cname}", fontsize=9, loc="left")
        if i == 0:
            ax.legend(loc="lower left", fontsize=7)
        x1, x2, y1, y2, loc = ZOOM[var][ckey]
        add_zoom(ax, df, var, x1, x2, y1, y2, loc)
    plt.tight_layout()
    plt.savefig(VAR_OUT[var], dpi=300, bbox_inches="tight")
    print(f"Saved {VAR_OUT[var]}")
    plt.show()