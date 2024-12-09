var HID = require("node-hid");

const devices = HID.devices();
console.log("devices:", devices);
