//SPDX-License-Identifier: UNLICENSED

pragma solidity 0.8.0;

import "@openzeppelin/contracts/access/Ownable.sol";
import "@openzeppelin/contracts/token/ERC20/ERC20.sol";

contract ClickToken is ERC20, Ownable {
    event OperatorAdded(address);
    event OperatorRemoved(address);

    mapping(address => bool) public operators;

    constructor() ERC20("RewardToken", "CLIK")  { }

    function mint(address _account, uint256 _amount) external {
        require(operators[msg.sender], "invalid operator");
        _mint(_account, _amount);
    }

    function burn(uint256 _amount) external {
        _burn(msg.sender, _amount);
    }

    function addOperator(address _account) external onlyOwner {
        require(!operators[_account], "already an operator");
        operators[_account] = true;
        emit OperatorAdded(_account);
    }

    function removeOperator(address _account) external onlyOwner {
        require(operators[_account], "not an operator");
        operators[_account] = false;
        emit OperatorRemoved(_account);
    }
}