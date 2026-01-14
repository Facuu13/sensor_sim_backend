import sys
import json

def main():
    ok = 0
    invalid_json = 0

    # estado: última lectura por (device_id, tipo_sensor)
    last = {}

    for line in sys.stdin:
        line = line.strip()
        if not line:
            continue

        try:
            msg = json.loads(line)
        except json.JSONDecodeError:
            invalid_json += 1
            continue

        ok += 1

        key = (msg.get("device_id"), msg.get("tipo_sensor"))
        last[key] = msg

        # cada 10 mensajes mostramos resumen
        if ok % 10 == 0:
            print_summary(ok, invalid_json, last)

def print_summary(ok, invalid_json, last):
    print("\n=== SUMMARY ===")
    print(f"ok={ok} invalid_json={invalid_json} sensors_tracked={len(last)}")

    # mostrar 1 línea por sensor (último valor)
    for (dev, stype), msg in last.items():
        # elegí qué mostrar: valor, bat, seq, status, timestamp
        print(f"- dev={dev} type={stype} valor={msg.get('valor')} bat={msg.get('bat')} seq={msg.get('seq')} status={msg.get('status')} ts={msg.get('timestamp')}")
    print("==============\n")

if __name__ == "__main__":
    main()
