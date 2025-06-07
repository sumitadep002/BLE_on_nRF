import asyncio
from bleak import BleakScanner
import sys

async def scan_loop(interval_sec=2):
    print("Starting continuous BLE scan...\n(Press Ctrl+C to stop)\n")

    while True:
        try:
            devices = await BleakScanner.discover(timeout=0.5, return_adv=True)

            found = False
            for address, (device, adv_data) in devices.items():
                if adv_data.local_name == 'BLE-NODE':
                    manufacturer_data = adv_data.manufacturer_data
                    if manufacturer_data:
                        for data in manufacturer_data.values():
                            if len(data) >= 4:
                                battery_mv = int.from_bytes(data[0:4], byteorder='little')
                                # Print on same line
                                sys.stdout.write(f"\rBattery Voltage: {battery_mv} mV  ")
                                sys.stdout.flush()
                                found = True
            if not found:
                sys.stdout.write("\rBLE-NODE not found.                     ")
                sys.stdout.flush()

            await asyncio.sleep(interval_sec)

        except KeyboardInterrupt:
            print("\nStopped scanning.")
            break

asyncio.run(scan_loop())
