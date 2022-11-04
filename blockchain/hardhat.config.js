require("@nomicfoundation/hardhat-toolbox");
require('dotenv').config()
const fs = require('fs');
 
const IOTEX_PRIVATE_KEY = process.env.IOTEX_PRIVATE_KEY;
/** @type import('hardhat/config').HardhatUserConfig */

task("addOperator", "Authorize w3bstream node as an operator")
  .addParam("operatoraddress", "Operator's address")
  .addParam("clicktokencontract", "ClickToken contract address")
  .setAction(async ({operatoraddress,clicktokencontract}) => {
    console.log("Adding Operator:", operatoraddress, ", to ClickToken contract: ", clicktokencontract);
 
    const ClickToken = await ethers.getContractFactory("ClickToken");
    const clickToken = await ClickToken.attach(clicktokencontract);
    let ret = await clickToken.addOperator(operatoraddress);
    console.log ("Registered new operator:", ret);
  });


module.exports = {
  solidity: {
    compilers: [
      {
        version: "0.8.0"
      }, 
      {
        version: "0.8.17"
      }
    ]
  },
  networks: {
    hardhat: {
      gas: 8500000,
    },
    testnet: {
      // These are the official IoTeX endpoints to be used by Ethereum clients
      // Testnet https://babel-api.testnet.iotex.io
      // Mainnet https://babel-api.mainnet.iotex.io
      url: `https://babel-api.testnet.iotex.io`,
 
      // Input your Metamask testnet account private key here
      accounts: [`${IOTEX_PRIVATE_KEY}`],
    },
  },
};