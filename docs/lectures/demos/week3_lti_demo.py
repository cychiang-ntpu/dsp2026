"""第 3 週課堂示範：impulse response、卷積、特徵函數、暫態與穩態。

用法：
    python3 week3_lti_demo.py            # 圖存到 ../figures/week3/
    python3 week3_lti_demo.py --show     # 另外開視窗顯示

只用 numpy 與 matplotlib；卷積與 LCCDE 都以最直白的迴圈寫出，方便對照講義公式。
"""
import os
import sys

import numpy as np
import matplotlib

if "--show" not in sys.argv:
    matplotlib.use("Agg")
import matplotlib.pyplot as plt

OUT_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "figures", "week3")


def impulse(N, shift=0):
    d = np.zeros(N)
    if 0 <= shift < N:
        d[shift] = 1.0
    return d


def lccde(b, a, x):
    """y[n] = sum_k b[k] x[n-k] - sum_{k>=1} a[k] y[n-k]，a[0] = 1，initial rest。"""
    y = np.zeros(len(x), dtype=complex if np.iscomplexobj(x) else float)
    for n in range(len(x)):
        acc = 0
        for k in range(len(b)):
            if n - k >= 0:
                acc += b[k] * x[n - k]
        for k in range(1, len(a)):
            if n - k >= 0:
                acc -= a[k] * y[n - k]
        y[n] = acc
    return y


def conv(x, h):
    """y[n] = sum_k x[k] h[n-k]，輸出長度 len(x)+len(h)-1。"""
    y = np.zeros(len(x) + len(h) - 1)
    for n in range(len(y)):
        for k in range(len(x)):
            if 0 <= n - k < len(h):
                y[n] += x[k] * h[n - k]
    return y


def freq_resp(b, a, w):
    """H(e^{jw}) = B(e^{jw}) / A(e^{jw})。"""
    zi = np.exp(-1j * np.outer(w, np.arange(max(len(b), len(a)))))
    B = zi[:, : len(b)] @ np.asarray(b, dtype=float)
    A = zi[:, : len(a)] @ np.asarray(a, dtype=float)
    return B / A


def stem(ax, n, v, title, color="C0"):
    ml, sl, bl = ax.stem(n, v, linefmt=color + "-", markerfmt=color + "o", basefmt="k-")
    plt.setp(ml, markersize=4)
    ax.set_title(title, fontsize=10)
    ax.set_xlabel("n")
    ax.grid(alpha=0.3)


def fig_impulse_responses():
    N = 20
    n = np.arange(N)
    d = impulse(N)
    systems = [
        ("Ideal delay: y[n] = x[n-3]", [0, 0, 0, 1], [1]),
        ("Moving average: y[n] = (x[n]+x[n-1]+x[n-2])/3", [1 / 3] * 3, [1]),
        ("Accumulator: y[n] = x[n] + y[n-1]", [1], [1, -1]),
        ("1st-order: y[n] = x[n] + 0.8 y[n-1]", [1], [1, -0.8]),
        ("Forward diff (non-causal): y[n] = x[n+1] - x[n]", None, None),
        ("2nd-order: y[n] = x[n] + 1.56cos(pi/6) y[n-1] - 0.81 y[n-2]", [1], [1, -2 * 0.9 * np.cos(np.pi / 6), 0.81]),
    ]
    fig, axes = plt.subplots(3, 2, figsize=(10, 8))
    for ax, (title, b, a) in zip(axes.flat, systems):
        if b is None:
            nn = np.arange(-5, N - 5)
            h = np.where(nn == -1, 1.0, 0.0) - np.where(nn == 0, 1.0, 0.0)
            stem(ax, nn, h, title, "C3")
        else:
            h = lccde(b, a, d)
            stem(ax, n, h, title, "C0" if len(a) == 1 else "C1")
        ax.set_ylabel("h[n]")
    fig.suptitle("Impulse responses h[n] = T{delta[n]}  (blue: FIR, orange: IIR, red: non-causal)")
    fig.tight_layout()
    return fig


def fig_convolution():
    x = np.array([1.0, 2.0, 3.0])
    h = np.array([1.0, 1.0, 0.5])
    y = conv(x, h)
    k = np.arange(-3, 7)
    n0 = 2
    xk = np.array([x[i] if 0 <= i < len(x) else 0 for i in k])
    hk = np.array([h[n0 - i] if 0 <= n0 - i < len(h) else 0 for i in k])
    fig, axes = plt.subplots(2, 2, figsize=(10, 6))
    stem(axes[0, 0], k, xk, "x[k] = {1, 2, 3}")
    stem(axes[0, 1], k, hk, f"h[{n0}-k]  (flip h[k], then shift by n={n0})", "C1")
    stem(axes[1, 0], k, xk * hk, f"x[k] h[{n0}-k]; sum = y[{n0}] = {np.sum(xk * hk):g}", "C2")
    stem(axes[1, 1], np.arange(len(y)), y, "y[n] = (x*h)[n], length 3+3-1 = 5", "C3")
    for ax in axes[0]:
        ax.set_xlabel("k")
    axes[1, 0].set_xlabel("k")
    fig.suptitle("Convolution = flip, shift, multiply, sum   (h[n] = {1, 1, 0.5})")
    fig.tight_layout()
    return fig


def fig_freq_response():
    w = np.linspace(-np.pi, np.pi, 1001)
    cases = [
        ("3-pt moving average", [1 / 3] * 3, [1]),
        ("1st-order IIR: y[n] = 0.9 y[n-1] + 0.1 x[n]", [0.1], [1, -0.9]),
    ]
    fig, axes = plt.subplots(2, 1, figsize=(9, 6), sharex=True)
    for label, b, a in cases:
        H = freq_resp(b, a, w)
        axes[0].plot(w / np.pi, np.abs(H), label=label)
        axes[1].plot(w / np.pi, np.angle(H) / np.pi, label=label)
    axes[0].axvline(2 / 3, color="k", ls=":", lw=1)
    axes[0].axvline(-2 / 3, color="k", ls=":", lw=1)
    axes[0].annotate("null at w = 2pi/3", xy=(2 / 3, 0), xytext=(0.72, 0.5),
                     arrowprops=dict(arrowstyle="->"))
    axes[0].set_ylabel("|H(e^{jw})|")
    axes[1].set_ylabel("angle H(e^{jw}) / pi")
    axes[1].set_xlabel("w / pi")
    for ax in axes:
        ax.grid(alpha=0.3)
        ax.legend()
    fig.suptitle("Eigenvalue of e^{jwn}: frequency response H(e^{jw}) = sum_k h[k] e^{-jwk}")
    fig.tight_layout()
    return fig


def fig_transient(b, a, title, N=80, w0=0.1 * np.pi):
    n = np.arange(N)
    x = np.exp(1j * w0 * n)  # e^{jw0 n} u[n]
    y = lccde(b, a, x)
    H0 = freq_resp(b, a, np.array([w0]))[0]
    yss = H0 * x
    yt = y - yss
    fig, axes = plt.subplots(2, 1, figsize=(10, 6.5), sharex=True)
    axes[0].plot(n, x.real, color="0.7", lw=1, label="Re x[n] = cos(w0 n) u[n]")
    axes[0].plot(n, yss.real, "C1--", lw=1.5, label="Re y_ss[n] = |H| cos(w0 n + angle H)")
    ml, sl, bl = axes[0].stem(n, y.real, linefmt="C0-", markerfmt="C0o", basefmt="k-", label="Re y[n]")
    plt.setp(ml, markersize=3)
    axes[0].legend(loc="upper right", fontsize=8)
    axes[0].set_title(title + f"   (w0 = 0.1 pi, |H| = {abs(H0):.3f}, angle H = {np.angle(H0):.3f} rad)", fontsize=10)
    axes[0].grid(alpha=0.3)
    mag = np.abs(yt)
    axes[1].semilogy(n, np.maximum(mag, 1e-17), "C3o-", ms=3, label="|y_t[n]| = |y[n] - y_ss[n]|")
    h = lccde(b, a, impulse(N + 400))
    bound = np.array([np.sum(np.abs(h[k + 1:])) for k in range(N)])
    axes[1].semilogy(n, np.maximum(bound, 1e-17), "k:", label="bound: sum_{k>n} |h[k]|")
    axes[1].set_ylim(1e-6, 2)
    axes[1].set_xlabel("n")
    axes[1].legend(fontsize=8)
    axes[1].grid(alpha=0.3, which="both")
    fig.tight_layout()
    return fig


def main():
    os.makedirs(OUT_DIR, exist_ok=True)
    figs = {
        "fig1_impulse_responses.png": fig_impulse_responses(),
        "fig2_convolution.png": fig_convolution(),
        "fig3_frequency_response.png": fig_freq_response(),
        "fig4_transient_fir.png": fig_transient([1 / 8] * 8, [1], "FIR: 8-pt moving average (M = 7)"),
        "fig5_transient_iir.png": fig_transient([0.1], [1, -0.9], "IIR: y[n] = 0.9 y[n-1] + 0.1 x[n]"),
    }
    for name, fig in figs.items():
        path = os.path.join(OUT_DIR, name)
        fig.savefig(path, dpi=110)
        print("saved", os.path.normpath(path))
    if "--show" in sys.argv:
        plt.show()


if __name__ == "__main__":
    main()
