
async function main() {

  const [deployer] = await ethers.getSigners();
  console.log("Deploying contracts with the account:", deployer.address);
  console.log("Address balance: %s IOTX", (await deployer.getBalance()).toString());

  const RewardToken = await ethers.getContractFactory("RewardToken");

  const rewardToken = await RewardToken.deploy();

  await rewardToken.deployed();

  console.log("adding owner as operator")

  await rewardToken.addOperator(deployer.address);

  console.log("deployer address: ", deployer.address)


  console.log(
    `Contract deployed to ${rewardToken.address}`
  );
}

// We recommend this pattern to be able to use async/await everywhere
// and properly handle errors.
main().catch((error) => {
  console.error(error);
  process.exitCode = 1;
});