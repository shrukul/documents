<?php
include_once 'db.php';
class User{
private $db;
private $db_table = "users";
public function __construct(){
$this->db = new DbConnect();
}
public function isLoginExist($email, $pin){
$query = "select * from " . $this->db_table . " where email = '$email' AND pin = '$pin' Limit 1";
$result = mysqli_query($this->db->getDb(), $query);
if(mysqli_num_rows($result) > 0){
mysqli_close($this->db->getDb());
return true;
}
mysqli_close($this->db->getDb());
return false;
}
public function idLogin($id, $pin){
$query = "select * from " . $this->db_table . " where id = '$id' AND pin = '$pin' Limit 1";
$result = mysqli_query($this->db->getDb(), $query);
if(mysqli_num_rows($result) > 0){
mysqli_close($this->db->getDb());
return true;
}
mysqli_close($this->db->getDb());
return false;
}
public function idExist(($id)){
$query = "select * from " . $this->db_table . " where id = '$id' Limit 1";
$result = mysqli_query($this->db->getDb(), $query);
if(mysqli_num_rows($result) > 0){
mysqli_close($this->db->getDb());
return true;
}
mysqli_close($this->db->getDb());
return false;
}
public function createNewRegisterUser($name, $email, $id, $pin){
$query = "insert into users (name, email, id, pin) values ('$name', '$email', '$id', '$pin')";
$inserted = mysqli_query($this->db->getDb(), $query);
if($inserted == 1){
$json['success'] = 1;
}else{
$json['success'] = 0;
}
mysqli_close($this->db->getDb());
return $json;
}
public function loginUsers($email, $pin){
$json = array();
$canUserLogin = $this->isLoginExist($email, $pin);
if($canUserLogin){
$json['success'] = 1;
}else{
$json['success'] = 0;
}
return $json;
}
public function tranfer($sender_id,$receiver_id,$amount){
$query = "update " . $this->db_table . "set balance =  balance - '$amount' where id = '$sender_id' Limit 1";
$query = "update " . $this->db_table . "set balance =  balance + '$amount' where id = '$receiver_id' Limit 1";
$result = mysqli_query($this->db->getDb(), $query);
}
public function billShare($sender_id, $receiver_id, $sender_pin, $amount){
$json = array();
$canUserALogin = $this->idExist($sender_id);
$canUserBLogin = $this->idExist($receiver_id);
if($canUserALogin && $canUserBLogin){
if(id_login($sender_id,$sender_pin)){
transfer($sender_id,$receiver_id,$amount);
$json['success'] = 1;
}
else{
$json['success'] = 0;
}
}else{
$json['success'] = 0;
}
return $json;
}
}
?>
