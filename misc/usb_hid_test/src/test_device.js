const HID = require("node-hid");
const assert = require("assert");

const TARGET_VENDOR_ID = 0xfba5;
const TARGET_PRODUCT_ID = 0x0001;
const message = "Hello world.";

const deviceInfos = HID.devices();

const deviceInfo = deviceInfos.find(
  (device) =>
    device.vendorId == TARGET_VENDOR_ID && device.productId == TARGET_PRODUCT_ID
);
assert(deviceInfo);
console.log("Found device: ", deviceInfo);

const messageBuffer = Array.from(message, (c) => c.charCodeAt(0)); // String to array of ascii codes.
messageBuffer.unshift(0); // 0 for report ID.
assert(messageBuffer.length <= 64);
const device = new HID.HID(deviceInfo.path);

device.on("data", (data) => {
  console.log(`Receive data: ${data.toString("ascii")}`);
});

device.on("error", (e) => {
  console.log(`Error: ${e}`);
});

setInterval(() => {
  device.write(messageBuffer);
  console.log(`Writting: ${messageBuffer}.`);
}, 500);
