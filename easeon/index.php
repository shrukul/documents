<?php
require_once 'users.php';
$name = "";
$pin = "";
$email = "";
$id = "";
if(isset($_POST['name'])){
$name = $_POST['name'];
}
if(isset($_POST['id'])){
$id = $_POST['id'];
}
if(isset($_POST['pin'])){
$pin = $_POST['pin'];
}
if(isset($_POST['email'])){
$email = $_POST['email'];
}
if(isset($_POST['sender_id'])){
$sender_id = $_POST['sender_id'];
}
if(isset($_POST['receiver_id'])){
$receiver_id = $_POST['receiver_id'];
}
if(isset($_POST['sender_pin'])){
$sender_pin = $_POST['sender_pin'];
}
if(isset($_POST['amount'])){
$amount = $_POST['amount'];
}
// Instance of a User class
$userObject = new User();
// Registration of new user
if(!empty($name) && !empty($id) && !empty($email)){
$pin = substr(str_shuffle(str_repeat('0123456789', mt_rand(1,4))),1,4);
//$hashed_password = md5($password);
$json_registration = $userObject->createNewRegisterUser($name, $email, $id, $pin);
echo json_encode($json_registration);
}
// User Login
if( !empty($email) && !empty($pin)){
//$hashed_password = md5($password);
//$json_array = $userObject->loginUsers($email, $hashed_password);
$json_array = $userObject->loginUsers($email, $pin);
echo json_encode($json_array);
}
// Bill Share
if( !empty($sender_id) && !empty($receiver_id) && !empty($sender_pin && !empty($amount)){
//$hashed_password = md5($password);
//$json_array = $userObject->loginUsers($email, $hashed_password);
$json_array = $userObject->billShare($sender_id, $receiver_id, $sender_pin, $amount);
echo json_encode($json_array);
}
?>
