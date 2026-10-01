# Day-2-4：以離散訊號處理模擬 RC 低通濾波器

[← day02_3_impedance_rc_lowpass.md](day02_3_impedance_rc_lowpass.md) ｜ [Day-2 總覽](day02_continuous_to_discrete.md) ｜ [day02_supp_rlc_filter_experiment.md →](day02_supp_rlc_filter_experiment.md)

## 3.1. Simulation of RC Low-Pass Filter by Discrete Signal Processing

以下投影片推導由 x(t) = RC·dy/dt + y(t) 離散化得到
y[n] = (RC/(RC+τ))·y[n−1] + (τ/(RC+τ))·x[n]，即 [HW1](../../assignments/hw1_rc_lowpass/) 式 (8)。

![](https://i.imgur.com/QTorNFt.png)

![](https://i.imgur.com/2HOJ05Y.png)

![](https://i.imgur.com/5OpsCf5.png)

![](https://i.imgur.com/gUNzyTT.png)

![](https://i.imgur.com/LtfW2Z1.png)

---

[← day02_3_impedance_rc_lowpass.md](day02_3_impedance_rc_lowpass.md) ｜ [Day-2 總覽](day02_continuous_to_discrete.md) ｜ [day02_supp_rlc_filter_experiment.md →](day02_supp_rlc_filter_experiment.md)
