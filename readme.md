# Mini IoT — Sensor Firmware (C) + Backend Ingestor (Python) — 100% Simulado

Este repositorio es un mini-proyecto para practicar **C** y **Python** con un enfoque realista de **IoT/Embedded**, pero **sin hardware**.  
La idea es simular un “firmware” que genera lecturas de sensores y un “backend” que las ingiere, valida y almacena, como si fuera un sistema real en producción.s

## Objetivo

- Practicar **C** con un estilo cercano a firmware: estructuras, estados, validación, buffers, timing, logs.
- Practicar **Python** como backend IoT: ingesta de datos, parsing, validación, almacenamiento y reporting.
- Mantener un flujo de trabajo “real”: roadmap, entregables incrementales, testing básico y documentación.

---

## Arquitectura (alto nivel)

**[sensor_sim (C)] → stdout (JSON Lines) → pipe → [ingest (Python)] → almacenamiento + reporte**

- El simulador (C) emite un mensaje por línea (JSON) con:
  - timestamp (`ts`)
  - device id (`device`)
  - valores de sensores (ej: `temp_c`, `hum_pct`)
  - batería (`bat_v`)
  - estado (`status`)
  - número de secuencia (`seq`)

- El backend (Python) consume esas líneas desde `stdin`, valida contenido y mantiene métricas.

---

## Formato de mensajes

Usamos **JSON Lines** (una línea = un mensaje). Ejemplo:

```json
{"ts":1700000000,"device":"dev-01","temp_c":23.4,"hum_pct":51.2,"bat_v":3.98,"status":"OK","seq":12}
