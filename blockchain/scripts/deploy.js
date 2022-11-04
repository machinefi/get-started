async function main() {

  const [deployer] = await ethers.getSigners();
  console.log("Deploying contracts with the account:", deployer.address);
  console.log("Address balance: %s IOTX", (await deployer.getBalance()).toString());

  const ClickToken = await ethers.getContractFactory("ClickToken");

  const clickToken = await ClickToken.deploy();

  await clickToken.deployed();

  console.log("adding owner as operator")

  await clickToken.addOperator(deployer.address);

  console.log("deployer address: ", deployer.address)

  console.log(
    `Contract deployed to ${clickToken.address}`
  );

}



// We recommend this pattern to be able to use async/await everywhere
// and properly handle errors.
main().catch((error) => {
  console.error(error);
  process.exitCode = 1;
});