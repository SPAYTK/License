# 💠 Quantum Superposition System Firmware

**Autor:** Alberto Sampayo Iglesias  
**Licencia:** Apache 2.0  
**Versión inicial:** v1.0 - Abril 2025

---

⚛️ Sistema experimental de computación cuántica basada en:

- Excitación iónica por metaconductores.
- Lectura por 14 cátodos hemisféricos.
- Evolución algorítmica en matrices complejas 36x36.
- Consenso de salida como frecuencia compleja derivada de energía proyectada en la esfera de Bloch.

---

## 💡 Salida digital

La salida del sistema es una frecuencia compleja:

\[
f_{\text{out}} = \frac{(x \cdot t) \cdot B(\theta, \phi)}{\left( \frac{9}{8} \cdot \frac{\pi}{3} \right)} \cdot e^{i\phi}
\]

Codificada en:

- `out_freq_real [15:0]` — parte real.
- `out_freq_imag [15:0]` — parte imaginaria.

---

## 📂 Estructura del proyecto

- `verilog/` → Módulos FPGA.
- `docs/` → Especificación técnica.
- `.gitignore` → Limpieza automática de binarios y temporales.

---

🚀 Listo para simulación, implementación y publicación como prior art.
