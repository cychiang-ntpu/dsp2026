"""Day-4 課堂示範：complex exponential 輸入 LTI 系統的穩態與暫態

x[n] = e^{j w0 n} u[n]（突然加上的複數指數）
y[n] = y_ss[n] + y_t[n]
  y_ss[n] = H(e^{j w0}) e^{j w0 n}
  y_t[n]  = -( sum_{k=n+1}^{inf} h[k] e^{-j w0 k} ) e^{j w0 n}

兩個例子：
  (A) FIR：長度 M+1 的移動平均，h[n] = 1/(M+1), 0 <= n <= M
  (B) IIR：h[n] = a^n u[n]

執行： python day04_transient_steady.py
輸出： ../figures/day04_*.png
"""
import os
import numpy as np
import matplotlib.pyplot as plt

OUT = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'figures')
os.makedirs(OUT, exist_ok=True)

w0 = 0.1 * np.pi          # 輸入頻率（rad/sample）
N = 60                    # 觀察長度
n = np.arange(N)
x = np.exp(1j * w0 * n)   # x[n] = e^{j w0 n} u[n]，n >= 0


def dtft(h, w):
    """H(e^{jw}) = sum_k h[k] e^{-jwk}（h 為有限長度或已截斷）"""
    k = np.arange(len(h))
    return np.exp(-1j * np.outer(w, k)) @ h


def run(h, title, fname, H0):
    y = np.convolve(x, h)[:N]           # 直接卷積：y[n] = sum_{k=0}^{n} h[k] x[n-k]
    y_ss = H0 * x                       # 穩態
    y_t = y - y_ss                      # 暫態

    fig, ax = plt.subplots(3, 1, figsize=(9, 7.5), sharex=True)
    ax[0].stem(n, x.real, basefmt=' ', linefmt='C0-', markerfmt='C0.')
    ax[0].set_ylabel('Re{x[n]}')
    ax[0].set_title(title)
    ax[1].stem(n, y.real, basefmt=' ', linefmt='C1-', markerfmt='C1.', label='Re{y[n]}')
    ax[1].plot(n, y_ss.real, 'k--', lw=1, label='Re{y_ss[n]}')
    ax[1].set_ylabel('output')
    ax[1].legend(loc='lower right', fontsize=8)
    ax[2].stem(n, np.abs(y_t), basefmt=' ', linefmt='C3-', markerfmt='C3.')
    ax[2].set_ylabel('|y_t[n]|')
    ax[2].set_xlabel('n')
    for a in ax:
        a.grid(alpha=0.3)
    fig.tight_layout()
    fig.savefig(os.path.join(OUT, fname), dpi=110)
    plt.close(fig)
    return y_t


# (A) FIR 移動平均，M = 10
M = 10
hA = np.ones(M + 1) / (M + 1)
HA = dtft(hA, np.array([w0]))[0]
ytA = run(hA, f'(A) FIR moving average, M = {M}, w0 = 0.1π', 'day04_fir_transient.png', HA)
print(f'FIR: |H(e^jw0)| = {abs(HA):.4f}, angle = {np.angle(HA):+.4f} rad;'
      f' max|y_t[n]| for n >= M: {np.abs(ytA[M:]).max():.2e}')

# (B) IIR h[n] = a^n u[n]，a = 0.8（截斷到夠長，誤差 < 1e-12）
a = 0.8
hB = a ** np.arange(200)
HB = 1 / (1 - a * np.exp(-1j * w0))   # 閉式解
ytB = run(hB, f'(B) IIR h[n] = a^n u[n], a = {a}, w0 = 0.1π', 'day04_iir_transient.png', HB)
bound = np.abs(a * np.exp(-1j * w0)) ** (n + 1) / np.abs(1 - a * np.exp(-1j * w0))
print(f'IIR: |H(e^jw0)| = {abs(HB):.4f}, angle = {np.angle(HB):+.4f} rad;'
      f' max | |y_t| - a^(n+1)/|1-a e^-jw0| | = {np.abs(np.abs(ytB) - bound).max():.2e}')

# 頻率響應：兩系統的 |H| 與 ∠H
w = np.linspace(-np.pi, np.pi, 1001)
fig, ax = plt.subplots(2, 1, figsize=(9, 5.5), sharex=True)
for h, lab in [(hA, f'FIR M={M}'), (hB, f'IIR a={a}')]:
    H = dtft(h, w)
    ax[0].plot(w / np.pi, np.abs(H), label=lab)
    ax[1].plot(w / np.pi, np.angle(H), label=lab)
for a_ in ax:
    a_.axvline(w0 / np.pi, color='k', ls=':', lw=1)
    a_.grid(alpha=0.3)
ax[0].set_ylabel('|H(e^{jw})|')
ax[1].set_ylabel('angle H (rad)')
ax[1].set_xlabel('w / π')
ax[0].legend()
ax[0].set_title('Frequency response (dotted line: w0)')
fig.tight_layout()
fig.savefig(os.path.join(OUT, 'day04_freq_response.png'), dpi=110)
plt.close(fig)
print('figures written to', os.path.normpath(OUT))
