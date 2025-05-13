import asyncio
from bleak import BleakScanner

async def main():
    devices = await BleakScanner.discover(5.0, return_adv=True)
    for d in devices:
        if(devices[d][1].local_name == 'BLE-BEACON'):
            print("Found it")

asyncio.run(main())
